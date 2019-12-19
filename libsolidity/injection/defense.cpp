//
// Created by Jay Ele on 2019/12/12.
//

#include "defense.h"

using namespace uds;


void Defense::prepareVarDeclarations() {
    // prepare lists
    this->varDeclarations["whiteList"] = new VarDeclaration("mapping(address => bool) public", "whiteList");
    this->varDeclarations["blackList"] = new VarDeclaration("mapping(address => bool) public", "blackList");
    this->varDeclarations["greyList"] = new VarDeclaration("mapping(address => uint256) public", "greyList");

    // prepare interval restrictions
    this->varDeclarations["accessTime"] = new VarDeclaration("mapping(address => uint256)", "accessTime");
    this->varDeclarations["accessTimeInterval"] = new VarDeclaration("mapping(address => uint256)", "accessTimeInterval");
    this->varDeclarations["funcAccessTime"] = new VarDeclaration("mapping(bytes4 => uint256)", "funcAccessTime");
    this->varDeclarations["funcAccessTimeInterval"] = new VarDeclaration("mapping(bytes4 => uint256)", "funcAccessTimeInterval");

    // prepare control variables
    this->varDeclarations["securityController"] = new VarDeclaration("address public", "securityController", this->securityController);
    this->varDeclarations["superUser"] = new VarDeclaration("address public", "superUser");
    this->varDeclarations["securityLevel"] = new VarDeclaration("uint8 public", "securityLevel", to_string(this->securityLevel));
}

void Defense::prepareInitStatements() {
    this->initStatements.push_back(InitStatement("superUser = tx.origin;", "superUser"));
}

void Defense::prepareEvents() {
    vector<string> params;
    params.push_back("address target");
    params.push_back("string targetList");
    params.push_back("uint val");
    this->events["listUpdated"] = new Event("listUpdated", params);

    params.clear();
    params.push_back("address newOne");
    this->events["superUserChanged"] = new Event("superUserChanged", params);
    this->events["securityControllerChanged"] = new Event("securityControllerChanged", params);

    params.clear();
    params.push_back("uint newLevel");
    this->events["securityLevelChanged"] = new Event("securityLevelChanged", params);
}

void Defense::prepareModifiers() {
    // modifier accessControl
    string block =
            "if (whiteList[tx.origin] == false && whiteList[msg.sender] == false) {\n"
            "    require(\n"
            "        blackList[tx.origin] == false && blackList[msg.sender] == false,\n"
            "        \"blackList\"\n"
            "    );\n"
            "    if (greyList[tx.origin] > block.timestamp || greyList[msg.sender] > block.timestamp) {\n"
            "        require(\n"
            "            accessTime[tx.origin] < block.timestamp && accessTime[msg.sender] < block.timestamp, \n"
            "            \"greyList\"\n"
            "        );\n"
            "        uint256 a = accessTimeInterval[tx.origin];\n"
            "        uint256 b = accessTimeInterval[msg.sender];\n"
            "        accessTime[tx.origin] = accessTime[msg.sender] = block.timestamp + a > b? a: b;\n"
            "    }\n"
            "    if (securityLevel > 1) {\n"
            "        require(funcAccessTime[msg.sig] < block.timestamp, \"function access restricted.\");\n"
            "        funcAccessTime[msg.sig] = block.timestamp + funcAccessTimeInterval[msg.sig];\n"
            "    }\n"
            "}\n"
            "_;";
    this->modifiers["accessControl"] = new Modifier("accessControl", block);

    // modifier onlySuperUser
    block = "require(tx.origin == superUser, \"only superUser allowed.\");\n"
            "_;";
    this->modifiers["onlySuperUser"] = new Modifier("onlySuperUser", block);

    // modifier onlySuperUserOrSecurityController
    block = "require(\n"
            "    msg.sender == securityController || msg.sender == superUser, \n"
            "    \"only superUser or securityController allowed.\"\n"
            ");\n"
            "_;";
    this->modifiers["onlySuperUserOrSecurityController"] = new Modifier("onlySuperUserOrSecurityController", block);
}

void Defense::prepareFunctions(bool super) {
    // function changeSecurityLevel
    vector<string> modifierNames;
    modifierNames.push_back("onlySuperUserOrSecurityController");
    vector<string> params;
    params.push_back("uint8 newLevel");
    vector<string> returns;
    string block = "securityLevel = newLevel;\n"
                   "emit securityLevelChanged(securityLevel);";
    if (super)
        block = "super.changeSecurityLevel(newLevel);\n" + block;
    this->functions["changeSecurityLevel"] = new Function("changeSecurityLevel", block, modifierNames, params, returns);

    // function updateSecurityList
    params.clear();
    params.push_back("uint8 targetList");
    params.push_back("address target");
    params.push_back("uint val");
    block = "if (targetList == 0x00) {\n"
            "    require(tx.origin == superUser, \"only superUser allowed.\");\n"
            "    whiteList[target] = val == 1? true: false;\n"
            "    emit listUpdated(target, \"whiteList\", val);\n"
            "}else if (targetList == 0x01) {\n"
            "    blackList[target] = val == 1? true: false;\n"
            "    emit listUpdated(target, \"blackList\", val);\n"
            "}else if (targetList == 0x10) {\n"
            "    greyList[target] = val;\n"
            "    emit listUpdated(target, \"updateGreyList\", val);\n"
            "}else {\n"
            "    revert(\"illegal targetList.\");\n"
            "}";
    if (super)
        block = "super.updateSecurityList(targetList, target, val);\n" + block;
    this->functions["updateSecurityList"] = new Function("updateSecurityList", block, modifierNames, params, returns);

    // function updateAccessTimeInterval
    params.clear();
    params.push_back("address target");
    params.push_back("uint interval");
    block = "accessTimeInterval[target] = interval;";
    if (super)
        block = "super.updateAccessTimeInterval(target, interval);\n" + block;
    this->functions["updateAccessTimeInterval"] = new Function("updateAccessTimeInterval", block, modifierNames, params, returns);

    // function updateFuncAccessTimeInterval
    params.clear();
    params.push_back("bytes4 sig");
    params.push_back("uint interval");
    block = "funcAccessTimeInterval[sig] = interval;";
    if (super)
        block = "super.updateFuncAccessTimeInterval(sig, interval);\n" + block;
    this->functions["updateFuncAccessTimeInterval"] = new Function("updateFuncAccessTimeInterval", block, modifierNames, params, returns);

    // function changeSuperUser
    params.clear();
    params.push_back("address newOne");
    modifierNames.clear();
    modifierNames.push_back("onlySuperUser");
    returns.push_back("address");
    block = "superUser = newOne;\n"
            "emit superUserChanged(superUser);\n"
            "return superUser;";
    if (super)
        block = "super.changeSuperUser(newOne);\n" + block;
    this->functions["changeSuperUser"] = new Function("changeSuperUser", block, modifierNames, params, returns);

    // function changeSecurityController
    block = "securityController = newOne;\n"
            "emit securityControllerChanged(securityController);\n"
            "return securityController;";
    if (super)
        block = "super.changeSecurityController(newOne);\n" + block;
    this->functions["changeSecurityController"] = new Function("changeSecurityController", block, modifierNames, params, returns);
}

void Defense::resetFunctions() {
    functions.clear();
}



