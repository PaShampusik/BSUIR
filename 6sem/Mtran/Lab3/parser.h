#pragma once
#include <filesystem>
#include <functional>
#include <unordered_map>

#include "error.h"
#include "lexer.h"
#include "tree.h"

// TODO store imports ???

using parseSpecFunction = std::function<SP<Spec>(token_type keyword, int iota)>;

template <typename T>
inline std::pair<T*, bool> isOfType(Node* ptr) {
    T* casted = dynamic_cast<T*>(ptr);
    return {(casted), casted != nullptr};
}

std::unordered_map<token_type, bool> stmtStart = {
    {token_type::BREAK, true},  {token_type::CONST, true},       {token_type::CONTINUE, true},
    {token_type::DEFER, true},  {token_type::FALLTHROUGH, true}, {token_type::FOR, true},
    {token_type::GOTO, true},   {token_type::IF, true},          {token_type::RETURN, true},
    {token_type::SWITCH, true}, {token_type::TYPE, true},        {token_type::VAR, true},
};

std::unordered_map<token_type, bool> declStart = {
    {token_type::IMPORT, true},
    {token_type::CONST, true},
    {token_type::TYPE, true},
    {token_type::VAR, true},
};

std::unordered_map<token_type, bool> exprEnd = {
    {token_type::COMMA, true},  {token_type::COLON, true},  {token_type::SEMICOLON, true},
    {token_type::RPAREN, true}, {token_type::RBRACE, true}, {token_type::RBRACK, true},
};

struct field {
    SP<IdentExpr> name;
    SP<Expr> typ;
};

class parser {
   private:
    const int maxNestLev = 1e5;

    lexer lxr;
    Tokens tokens_;
    Errors errors_;
    V<SP<Decl>> decls_;

    // next token
    pos_t pos_;
    token_type tok_;
    std::string lit_;  // token literal

    int nestLev_ = 0;
    int exprLev_ = 0;
    bool inRhs_ = false;
    size_t cur_ = 0;
    pos_t syncPos_;
    int syncCnt_ = 0;

    void incNestLev();
    void decNestLev();
    pos_t expect(token_type token);
    pos_t expect2(token_type token);
    void next();
    pos_t expectClosing(token_type tok, std::string context);
    void expectSemi();
    bool atComma(std::string context, token_type follow);
    void assert(bool cond, std::string msg);
    void advance(const std::unordered_map<token_type, bool> to);
    SP<IdentExpr> parseIdent();
    V<SP<IdentExpr>> parseIdentList();
    V<SP<Expr>> parseExprList();
    V<SP<Expr>> parseList(bool inRhs);
    SP<Expr> parseType();
    SP<Expr> parseQualifiedIdent(SP<IdentExpr> ident);
    SP<Expr> parseTypeName(SP<IdentExpr> ident);
    SP<ArrayTypeExpr> parseArrayType(pos_t lbrack, SP<Expr> len);
    std::pair<SP<IdentExpr>, SP<Expr>> parseArrayFieldOrTypeInstance(SP<IdentExpr> x);
    SP<Field> parseFieldDecl();
    SP<StructTypeExpr> parseStructType();
    SP<StarExpr> parsePointerType();
    SP<EllipsisExpr> parseDotsType();
    field parseParamDecl(SP<IdentExpr> name, bool typeSetsOk);
    V<SP<Field>> parseParameterList(SP<IdentExpr> name0, SP<Expr> typ0, token_type closing);
    std::pair<SP<FieldList>, SP<FieldList>> parseParameters(bool acceptTParams);
    SP<FieldList> parseResult();
    SP<FuncTypeExpr> parseFuncType();
    SP<Field> parseMethodSpec();
    SP<Expr> embeddedElem(SP<Expr> x);
    SP<Expr> embeddedTerm();
    SP<InterfaceTypeExpr> parseInterfaceType();
    SP<MapTypeExpr> parseMapType();
    SP<Expr> parseTypeInstance(SP<Expr> typ);
    SP<Expr> tryIdentOrType();
    V<SP<Stmt>> parseStmtList();
    SP<BlockStmt> parseBody();
    SP<BlockStmt> parseBlockStmt();
    SP<Expr> parseFuncTypeOrLit();
    SP<Expr> parseOperand();
    SP<Expr> parseSelector(SP<Expr> x);
    SP<Expr> parseTypeAssertion(SP<Expr> x);
    SP<Expr> parseIndexOrSliceOrInstance(SP<Expr> x);
    SP<CallExpr> parseCallOrConversion(SP<Expr> fun);
    SP<Expr> parseValue();
    SP<Expr> parseElement();
    V<SP<Expr>> parseElementList();
    SP<Expr> parseLiteralValue(SP<Expr> typ);
    SP<Expr> unparen(SP<Expr> x);
    SP<Expr> parsePrimaryExpr(SP<Expr> x);
    SP<Expr> parseUnaryExpr();
    SP<Expr> parseBinaryExpr(SP<Expr> x, int prec1);
    std::pair<token_type, int> tokPrec();
    SP<Expr> parseExpr();
    SP<Expr> parseRhs();
    std::pair<SP<Stmt>, bool> parseSimpleStmt(int mode);
    SP<CallExpr> parseCallExpr(std::string callType);
    SP<Stmt> parseDeferStmt();
    SP<ReturnStmt> parseReturnStmt();
    SP<BranchStmt> parseBranchStmt(token_type tok);
    SP<Expr> makeExpr(SP<Stmt> s, std::string want);
    std::pair<SP<Stmt>, SP<Expr>> parseIfHeader();
    SP<IfStmt> parseIfStmt();
    SP<CaseClauseStmt> parseCaseClause();
    bool isTypeSwitchGuard(SP<Stmt> s);
    SP<Stmt> parseSwitchStmt();
    SP<Stmt> parseForStmt();
    SP<Stmt> parseStmt();
    SP<Spec> parseImportSpec(token_type,
                             int);  // do not need parameters, but match
                                    // parseSpecFunction interface
    SP<Spec> parseValueSpec(token_type keyword, int iota);
    SP<Spec> parseTypeSpec(token_type,
                           int);  // do not need parameters, but match
    // parseSpecFunction interface
    void parseGenericType(SP<TypeSpec> spec, pos_t openPos, SP<IdentExpr> name0, SP<Expr> typ0);
    SP<GenDecl> parseGenDecl(token_type keyword, parseSpecFunction f);
    SP<FuncDecl> parseFuncDecl();
    SP<Decl> parseDecl(std::unordered_map<token_type, bool> sync);
    SP<Expr> packIndexExpr(SP<Expr> x, pos_t lbrack, V<SP<Expr>> exprs, pos_t rbrack);

    // Error methods
    void errorExpected(pos_t pos, std::string msg);
    void error(pos_t pos, std::string msg);

   public:
    parser(const std::filesystem::path&);
    ~parser() {}
    void parseFile();
    void printErrors() const;

    std::string getTreeStr() const {
        if (!errors_.empty()) {
            return "";
        }
        std::string tree;
        for (const auto& decl : decls_) {
            tree += decl->Print(0);
        }
        return tree;
    }
};

void parser::errorExpected(pos_t pos, std::string msg) {
    msg = "expected " + msg;
    if (pos == pos_) {
        if (tok_ == token_type::SEMICOLON && lit_ == "\n") {
            msg += ", found newline";
        } else if (is_literal(tok_)) {
            msg += ", found " + lit_;
        } else {
            msg += ", found '" + type_string_map.at(tok_) + "'";
        }
    }
    error(pos, msg);
}

void parser::error(pos_t pos, std::string msg) { errors_.push_back({pos, msg}); }

SP<Expr> parser::packIndexExpr(SP<Expr> x, pos_t lbrack, V<SP<Expr>> exprs, pos_t rbrack) {
    switch (exprs.size()) {
        case 0:
            throw std::runtime_error("internal error: PackIndexExpr with empty expr slice");
        case 1:
            return std::make_shared<IndexExpr>(x, lbrack, exprs[0], rbrack);
        default:
            return std::make_shared<IndexListExpr>(x, lbrack, exprs, rbrack);
    }
}

parser::parser(const std::filesystem::path& path) : lxr(path) {
    lxr.tokenize();
    tokens_ = std::move(lxr.get_tokens());
    errors_ = std::move(lxr.get_errors());
    if (!tokens_.empty()) {
        auto tk = tokens_[0];
        tok_ = tk.type;
        lit_ = tk.lexeme;
        pos_ = tk.pos;
    }
}

void parser::incNestLev() {
    nestLev_++;
    if (nestLev_ > maxNestLev) {
        throw std::runtime_error("exceeded max nesting depth");
    }
}

void parser::decNestLev() { nestLev_--; }

void parser::next() {
    if (cur_ >= tokens_.size() - 1) {
        return;
    }
    auto token = tokens_[++cur_];
    pos_ = token.pos;
    tok_ = token.type;
    lit_ = token.lexeme;
}

pos_t parser::expect(token_type tok) {
    auto pos = pos_;
    if (tok_ != tok) {
        errorExpected(pos, "'" + type_string_map.at(tok) + "'");
    }
    next();
    return pos;
}

pos_t parser::expect2(token_type tok) {
    pos_t pos = NoPos;
    if (tok_ == tok) {
        pos = pos_;
    } else {
        errorExpected(pos_, "'" + type_string_map.at(tok) + "'");
    }
    next();
    return pos;
}

pos_t parser::expectClosing(token_type tok, std::string context) {
    if (tok_ != tok && tok_ == token_type::SEMICOLON && lit_ == "\n") {
        error(pos_, "missing ',' before newline in " + context);
        next();
    }
    return expect(tok);
}

void parser::expectSemi() {
    if (tok_ != token_type::RPAREN && tok_ != token_type::RBRACE) {
        switch (tok_) {
            case token_type::COMMA:
                errorExpected(pos_, "';'");
                // no break intentionally
            case token_type::SEMICOLON:
                next();
                break;
            default:
                errorExpected(pos_, "';'");
                advance(stmtStart);
                break;
        }
    }
}

bool parser::atComma(std::string context, token_type follow) {
    if (tok_ == token_type::COMMA) {
        return true;
    }
    if (tok_ != follow) {
        std::string msg = "missing ';'";
        if (tok_ == token_type::SEMICOLON && lit_ == "\n") {
            msg += " begore newline";
        }
        error(pos_, msg + " in " + context);
        return true;  // found error, report and continue parsing
    }
    return false;
}

void parser::assert(bool cond, std::string msg) {
    if (!cond) {
        throw std::runtime_error("internal parser error: " + msg);
    }
}

void parser::advance(std::unordered_map<token_type, bool> to) {
    while (tok_ != token_type::EOF_) {
        if (to[tok_]) {
            if (pos_ == syncPos_ && syncCnt_ < 10) {
                syncCnt_++;
                return;
            }
            if (pos_ > syncPos_) {
                syncPos_ = pos_;
                syncCnt_ = 0;
                return;
            }
        }
        next();
    }
}

SP<IdentExpr> parser::parseIdent() {
    auto pos = pos_;
    std::string name = "_";
    if (tok_ == token_type::IDENT) {
        name = lit_;
        next();
    } else {
        expect(token_type::IDENT);
    }
    return std::make_shared<IdentExpr>(pos, name);
}

V<SP<IdentExpr>> parser::parseIdentList() {
    V<SP<IdentExpr>> list;
    list.push_back(parseIdent());
    while (tok_ == token_type::COMMA) {
        next();
        list.push_back(parseIdent());
    }
    return list;
}

V<SP<Expr>> parser::parseExprList() {
    V<SP<Expr>> list;
    list.push_back(parseExpr());
    while (tok_ == token_type::COMMA) {
        next();
        list.push_back(parseExpr());
    }
    return list;
}

V<SP<Expr>> parser::parseList(bool inRhs) {
    bool old = inRhs_;
    inRhs_ = inRhs;
    auto list = parseExprList();
    inRhs_ = old;
    return list;
}

SP<Expr> parser::parseType() {
    auto typ = tryIdentOrType();
    if (typ == nullptr) {
        auto pos = pos_;
        errorExpected(pos, "type");
        advance(exprEnd);
        return std::make_shared<BadExpr>(pos, pos_);
    }
    return typ;
}

SP<Expr> parser::parseQualifiedIdent(SP<IdentExpr> ident) {
    auto typ = parseTypeName(ident);
    if (tok_ == token_type::LBRACK) {
        typ = parseTypeInstance(typ);
    }
    return typ;
}

SP<Expr> parser::parseTypeName(SP<IdentExpr> ident) {
    if (ident == nullptr) {
        ident = parseIdent();
    }
    if (tok_ == token_type::PERIOD) {
        next();
        auto sel = parseIdent();
        return std::make_shared<SelectorExpr>(ident, sel);
    }
    return ident;
}

// "[" has already been consumed, and lbrack is its position.
// If len != nullptr it is the already consumed array length.
SP<ArrayTypeExpr> parser::parseArrayType(pos_t lbrack, SP<Expr> len) {
    if (len == nullptr) {
        exprLev_++;
        if (tok_ == token_type::ELLIPSIS) {
            len = std::make_shared<EllipsisExpr>(pos_);
            next();
        } else if (tok_ != token_type::RBRACK) {
            len = parseRhs();
        }
        exprLev_--;
    }
    if (tok_ == token_type::COMMA) {
        error(pos_, "unexpected comma; expecting ]");
        next();
    }
    expect(token_type::RBRACK);
    auto elt = parseType();
    return std::make_shared<ArrayTypeExpr>(lbrack, len, elt);
}

std::pair<SP<IdentExpr>, SP<Expr>> parser::parseArrayFieldOrTypeInstance(SP<IdentExpr> x) {
    auto lbrack = expect(token_type::LBRACK);
    auto trailingComma = NoPos;
    V<SP<Expr>> args;
    if (tok_ != token_type::RBRACK) {
        exprLev_++;
        args.push_back(parseRhs());
        while (tok_ == token_type::COMMA) {
            auto comma = pos_;
            next();
            if (tok_ == token_type::RBRACK) {
                trailingComma = comma;
                break;
            }
            args.push_back(parseRhs());
        }
        exprLev_--;
    }

    auto rbrack = expect(token_type::RBRACK);
    if (args.empty()) {
        // x []E
        auto elt = parseType();
        return {x, std::make_shared<ArrayTypeExpr>(lbrack, nullptr, elt)};
    }

    if (args.size() == 1) {
        auto elt = tryIdentOrType();
        if (elt == nullptr) {
            if (trailingComma.IsValid()) {
                error(trailingComma, "unexpected comma; expecting ]");
            }
            return {x, std::make_shared<ArrayTypeExpr>(lbrack, args[0], elt)};
        }
    }

    return {nullptr, packIndexExpr(x, lbrack, args, rbrack)};
}

SP<Field> parser::parseFieldDecl() {
    V<SP<IdentExpr>> names;
    SP<Expr> typ;
    switch (tok_) {
        case token_type::IDENT: {
            auto name = parseIdent();
            if (tok_ == token_type::PERIOD || tok_ == token_type::STRING ||
                tok_ == token_type::SEMICOLON || tok_ == token_type::RBRACE) {
                typ = name;
                if (tok_ == token_type::PERIOD) {
                    typ = parseQualifiedIdent(name);
                }
            } else {
                names = {name};
                while (tok_ == token_type::COMMA) {
                    next();
                    names.push_back(parseIdent());
                }

                if (names.size() == 1 && tok_ == token_type::LBRACK) {
                    std::tie(name, typ) = parseArrayFieldOrTypeInstance(name);
                    if (name == nullptr) {
                        names.clear();
                    }
                } else {
                    typ = parseType();
                }
            }
            break;
        }
        case token_type::MUL: {
            auto star = pos_;
            next();
            if (tok_ == token_type::LPAREN) {
                // *(T)
                error(pos_, "cannot parenthesize embedded type");
                next();
                typ = parseQualifiedIdent(nullptr);
                if (tok_ == token_type::RPAREN) {
                    next();
                }
            } else {
                // *T
                typ = parseQualifiedIdent(nullptr);
            }
            typ = std::make_shared<StarExpr>(star, typ);
            break;
        }
        case token_type::LPAREN: {
            error(pos_, "cannot parenthesize embedded type");
            next();
            if (tok_ == token_type::MUL) {
                // (*T)
                auto star = pos_;
                next();
                typ = std::make_shared<StarExpr>(star, parseQualifiedIdent(nullptr));
            } else {
                // (T)
                typ = parseQualifiedIdent(nullptr);
            }
            if (tok_ == token_type::RPAREN) {
                next();
            }
            break;
        }
        default: {
            auto pos = pos_;
            errorExpected(pos, "field name or embedded type");
            advance(exprEnd);
            typ = std::make_shared<BadExpr>(pos, pos_);
            break;
        }
    }

    SP<BasicLitExpr> tag;
    if (tok_ == token_type::STRING) {
        tag = std::make_shared<BasicLitExpr>(pos_, tok_, lit_);
    }

    expectSemi();
    return std::make_shared<Field>(names, typ, tag);
}

SP<StructTypeExpr> parser::parseStructType() {
    auto pos = expect(token_type::STRUCT);
    auto lbrace = expect(token_type::LBRACE);
    V<SP<Field>> list;
    while (tok_ == token_type::IDENT || tok_ == token_type::MUL || tok_ == token_type::LPAREN) {
        list.push_back(parseFieldDecl());
    }
    auto rbrace = expect(token_type::RBRACE);

    return std::make_shared<StructTypeExpr>(pos, std::make_shared<FieldList>(lbrace, list, rbrace));
}

SP<StarExpr> parser::parsePointerType() {
    auto star = expect(token_type::MUL);
    auto base = parseType();
    return std::make_shared<StarExpr>(star, base);
}

SP<EllipsisExpr> parser::parseDotsType() {
    auto pos = expect(token_type::ELLIPSIS);
    auto elt = parseType();
    return std::make_shared<EllipsisExpr>(pos, elt);
}

field parser::parseParamDecl(SP<IdentExpr> name, bool typeSetsOk) {
    auto ptok = tok_;
    field f;
    if (name != nullptr) {
        tok_ = token_type::IDENT;
    } else if (typeSetsOk && tok_ == token_type::TILDE) {
        // "~" ...
        return field{nullptr, embeddedElem(nullptr)};
    }

    switch (tok_) {
        case token_type::IDENT:
            if (name != nullptr) {
                f.name = name;
                tok_ = ptok;
            } else {
                f.name = parseIdent();
            }
            switch (tok_) {
                case token_type::IDENT:
                case token_type::MUL:
                // TODO case token_type ::ARROW:
                case token_type::FUNC:
                // TODO case token_type ::CHAN:
                case token_type::MAP:
                case token_type::STRUCT:
                case token_type::INTERFACE:
                case token_type::LPAREN:
                    f.typ = parseType();
                    break;
                case token_type::LBRACK:
                    std::tie(f.name, f.typ) = parseArrayFieldOrTypeInstance(f.name);
                    break;
                case token_type::ELLIPSIS:
                    f.typ = parseDotsType();
                    break;
                case token_type::PERIOD:
                    f.typ = parseQualifiedIdent(f.name);
                    f.name = nullptr;
                    break;
                case token_type::TILDE:
                    if (typeSetsOk) {
                        f.typ = embeddedElem(nullptr);
                        return f;
                    }
                    break;
                case token_type::OR:
                    if (typeSetsOk) {
                        f.typ = embeddedElem(f.name);
                        f.name = nullptr;
                        return f;
                    }
                    break;
            }
            break;

        case token_type::MUL:
        // TODO case token_type ::ARROW:
        case token_type::FUNC:
        case token_type::LBRACK:
        // TODO case token_type ::CHAN:
        case token_type::MAP:
        case token_type::STRUCT:
        case token_type::INTERFACE:
        case token_type::LPAREN:
            f.typ = parseType();
            break;
        case token_type::ELLIPSIS:
            f.typ = parseDotsType();
            return f;
        default:
            errorExpected(pos_, "')");
            advance(exprEnd);
            break;
    }

    if (typeSetsOk && tok_ == token_type::OR && f.typ != nullptr) {
        f.typ = embeddedElem(f.typ);
    }

    return f;
}

V<SP<Field>> parser::parseParameterList(SP<IdentExpr> name0, SP<Expr> typ0, token_type closing) {
    V<SP<Field>> params;
    bool tparams = closing == token_type::RBRACK;
    bool typeSetOk = tparams;
    pos_t pos = pos_;
    if (name0 != nullptr) {
        pos = name0->Pos();
    }

    V<field> list;
    int named = 0;
    while (name0 != nullptr || tok_ != closing && tok_ != token_type::EOF_) {
        field par;
        if (typ0 != nullptr) {
            if (typeSetOk) {
                typ0 = embeddedElem(typ0);
            }
            par = field{name0, typ0};
        } else {
            par = parseParamDecl(name0, typeSetOk);
        }
        name0 = nullptr;
        typ0 = nullptr;
        if (par.name != nullptr || par.typ != nullptr) {
            list.push_back(par);
            if (par.name != nullptr && par.typ != nullptr) {
                named++;
            }
        }
        if (!atComma("parameter list", closing)) {
            break;
        }
        next();
    }

    if (list.empty()) {
        return params;
    }

    if (named == 0) {
        for (size_t i = 0; i < list.size(); i++) {
            auto& par = list[i];
            if (auto typ = par.name; typ != nullptr) {
                par.typ = typ;
                par.name = nullptr;
            }
        }
        if (tparams) {
            error(pos, "type parameters must be named");
        }
    } else if (named != list.size()) {
        bool ok = true;
        SP<Expr> typ;
        pos_t missingName = pos;
        for (int i = list.size() - 1; i >= 0; i--) {
            if (auto& par = list[i]; par.typ != nullptr) {
                typ = par.typ;
                if (par.name == nullptr) {
                    ok = false;
                    missingName = par.typ->Pos();
                    auto n = std::make_shared<IdentExpr>(NoPos, "_");
                    n->NamePos = typ->Pos();
                    par.name = n;
                }
            } else if (typ != nullptr) {
                par.typ = typ;
            } else {
                ok = false;
                missingName = par.name->Pos();
                par.typ = std::make_shared<BadExpr>(par.name->Pos(), pos_);
            }
        }
        if (!ok) {
            if (tparams) {
                error(missingName, "type parameters must be named");
            } else {
                error(pos, "mixed named and unnamed parameters");
            }
        }
    }

    if (named == 0) {
        for (const auto& par : list) {
            assert(par.typ != nullptr, "nullptr type in unnamed parameter list");
            params.push_back(std::make_shared<Field>(V<SP<IdentExpr>>(), par.typ, nullptr));
        }
        return params;
    }

    V<SP<IdentExpr>> names;
    SP<Expr> typ;
    auto addParams = [&params, &typ, &names, this]() {
        assert(typ != nullptr, "nullptr type in named parameter list");
        auto field = std::make_shared<Field>(names, typ, nullptr);
        params.push_back(field);
        names.clear();
    };
    for (const auto& par : list) {
        if ((!par.typ && typ) || !(!par.typ && !typ) && *par.typ != *typ) {
            if (names.size() > 0) {
                addParams();
            }
            typ = par.typ;
        }
        names.push_back(par.name);
    }
    if (names.size() > 0) {
        addParams();
    }
    return params;
}

std::pair<SP<FieldList>, SP<FieldList>> parser::parseParameters(bool acceptTParams) {
    SP<FieldList> tparams, params;

    if (acceptTParams && tok_ == token_type::LBRACK) {
        auto opening = pos_;
        next();
        auto list = parseParameterList(nullptr, nullptr, token_type::RBRACK);
        pos_t rbrack = expect(token_type::RBRACK);
        tparams = std::make_shared<FieldList>(opening, list, rbrack);
        if (tparams->NumFields() == 0) {
            error(tparams->Closing, "empty type parameter list");
            tparams = nullptr;
        }
    }

    pos_t opening = expect(token_type::LPAREN);

    V<SP<Field>> fields;
    if (tok_ != token_type::RPAREN) {
        fields = parseParameterList(nullptr, nullptr, token_type::RPAREN);
    }

    pos_t rparen = expect(token_type::RPAREN);
    params = std::make_shared<FieldList>(opening, fields, rparen);

    return {tparams, params};
}

SP<FieldList> parser::parseResult() {
    if (tok_ == token_type::LPAREN) {
        auto [_, results] = parseParameters(false);
        return results;
    }
    auto typ = tryIdentOrType();
    if (typ != nullptr) {
        V<SP<Field>> list;
        list.push_back(std::make_shared<Field>(V<SP<IdentExpr>>(), typ, nullptr));
        return std::make_shared<FieldList>(NoPos, list, NoPos);
    }
    return nullptr;
}

SP<FuncTypeExpr> parser::parseFuncType() {
    auto pos = expect(token_type::FUNC);
    auto [tparams, params] = parseParameters(true);
    if (tparams != nullptr) {
        error(tparams->Pos(), "function type must have no type parameters");
    }
    auto results = parseResult();
    return std::make_shared<FuncTypeExpr>(pos, nullptr, params, results);
}

SP<Field> parser::parseMethodSpec() {
    V<SP<IdentExpr>> idents;
    SP<Expr> typ;
    auto x = parseTypeName(nullptr);
    if (auto ident = dynamic_cast<IdentExpr*>(x.get()); ident != nullptr) {
        switch (tok_) {
            case token_type::LBRACK: {
                pos_t lbrack = pos_;
                next();
                exprLev_++;
                auto x = parseExpr();
                exprLev_--;
                if (auto name0 = dynamic_cast<IdentExpr*>(x.get());
                    name0 != nullptr && tok_ != token_type::COMMA && tok_ != token_type::RBRACK) {
                    parseParameterList(std::make_shared<IdentExpr>(*name0), nullptr,
                                       token_type::RBRACK);
                    expect(token_type::RBRACK);
                    error(lbrack, "interface method must have no type parameters");

                    auto [_, params] = parseParameters(false);
                    auto results = parseResult();
                    idents = {std::make_shared<IdentExpr>(*ident)};
                    typ = std::make_shared<FuncTypeExpr>(NoPos, nullptr, params, results);
                } else {
                    V<SP<Expr>> list = {x};
                    if (atComma("type argument list", token_type::RBRACK)) {
                        exprLev_++;
                        next();
                        while (tok_ != token_type::RBRACK && tok_ != token_type::EOF_) {
                            list.push_back(parseType());
                            if (!atComma("type argument list", token_type::RBRACK)) {
                                break;
                            }
                            next();
                        }
                        exprLev_--;
                    }
                    auto rbrack = expectClosing(token_type::RBRACK, "type argument list");
                    typ = packIndexExpr(std::make_shared<IdentExpr>(*ident), lbrack, list, rbrack);
                }
                break;
            }
            case token_type::LPAREN: {
                auto [_, params] = parseParameters(false);
                auto results = parseResult();
                idents.clear();
                idents.push_back(std::make_shared<IdentExpr>(*ident));
                typ = std::make_shared<FuncTypeExpr>(NoPos, nullptr, params, results);
                break;
            }
            default:
                typ = x;
                break;
        }
    } else {
        typ = x;
        if (tok_ == token_type::LBRACK) {
            typ = parseTypeInstance(typ);
        }
    }
    return std::make_shared<Field>(idents, typ, nullptr);
}

SP<Expr> parser::embeddedElem(SP<Expr> x) {
    if (x == nullptr) {
        x = embeddedTerm();
    }
    while (tok_ == token_type::OR) {
        auto t = BinaryExpr();
        t.OpPos = pos_;
        t.Op = token_type::OR;
        next();
        t.X = x;
        t.Y = embeddedTerm();
        x = std::make_shared<BinaryExpr>(t);
    }
    return x;
}

SP<Expr> parser::embeddedTerm() {
    if (tok_ == token_type::TILDE) {
        auto t = UnaryExpr();
        t.OpPos = pos_;
        t.Op = token_type::TILDE;
        next();
        t.X = parseType();
        return std::make_shared<UnaryExpr>(t);
    }

    auto t = tryIdentOrType();
    if (t == nullptr) {
        pos_t pos = pos_;
        errorExpected(pos, "~ term or type");
        advance(exprEnd);
        return std::make_shared<BadExpr>(pos, pos_);
    }

    return t;
}

SP<InterfaceTypeExpr> parser::parseInterfaceType() {
    pos_t pos = expect(token_type::INTERFACE);
    pos_t lbrace = expect(token_type::LBRACE);
    V<SP<Field>> list;
    bool continueLoop = true;
    while (continueLoop) {
        switch (tok_) {
            case token_type::IDENT: {
                auto f = parseMethodSpec();
                if (f->Names.empty()) {
                    f->Type = embeddedElem(f->Type);
                }
                expectSemi();
                list.push_back(f);
                break;
            }
            case token_type::TILDE: {
                auto typ = embeddedElem(nullptr);
                expectSemi();
                list.push_back(std::make_shared<Field>(V<SP<IdentExpr>>(), typ, nullptr));
                break;
            }
            default: {
                if (auto t = tryIdentOrType(); t != nullptr) {
                    auto typ = embeddedElem(t);
                    expectSemi();
                    list.push_back(std::make_shared<Field>(V<SP<IdentExpr>>(), typ, nullptr));
                } else {
                    continueLoop = false;
                    break;
                }
            }
        }
    }
    pos_t rbrace = expect(token_type::RBRACE);
    return std::make_shared<InterfaceTypeExpr>(pos,
                                               std::make_shared<FieldList>(lbrace, list, rbrace));
}

SP<MapTypeExpr> parser::parseMapType() {
    pos_t pos = expect(token_type::MAP);
    expect(token_type::LBRACK);
    auto key = parseType();
    expect(token_type::RBRACK);
    auto value = parseType();
    return std::make_shared<MapTypeExpr>(pos, key, value);
}

SP<Expr> parser::parseTypeInstance(SP<Expr> typ) {
    pos_t opening = expect(token_type::LBRACK);
    exprLev_++;
    V<SP<Expr>> list;
    while (tok_ != token_type::RBRACK && tok_ != token_type::EOF_) {
        list.push_back(parseType());
        if (!atComma("type argument list", token_type::RBRACK)) {
            break;
        }
        next();
    }
    exprLev_--;

    pos_t closing = expectClosing(token_type::RBRACK, "type argument list");

    if (list.empty()) {
        errorExpected(closing, "type argument list");
        return std::make_shared<IndexExpr>(
            typ, opening, std::make_shared<BadExpr>(opening + 1, closing), closing);
    }

    return packIndexExpr(typ, opening, list, closing);
}

SP<Expr> parser::tryIdentOrType() {
    incNestLev();
    SP<Expr> ret = nullptr;
    switch (tok_) {
        case token_type::IDENT: {
            auto typ = parseTypeName(nullptr);
            if (tok_ == token_type::LBRACK) {
                typ = parseTypeInstance(typ);
            }
            ret = typ;
            break;
        }
        case token_type::LBRACK: {
            pos_t lbrack = expect(token_type::LBRACK);
            ret = parseArrayType(lbrack, nullptr);
            break;
        }
        case token_type::STRUCT:
            ret = parseStructType();
            break;
        case token_type::MUL:
            ret = parsePointerType();
            break;
        case token_type::FUNC:
            ret = parseFuncType();
            break;
        case token_type::INTERFACE:
            ret = parseInterfaceType();
            break;
        case token_type::MAP:
            ret = parseMapType();
            break;
        // TODO case CHAN, ARROW
        case token_type::LPAREN: {
            pos_t lparen = pos_;
            next();
            auto typ = parseType();
            pos_t rparen = expect(token_type::RPAREN);
            ret = std::make_shared<ParenExpr>(lparen, typ, rparen);
            break;
        }
    }
    decNestLev();
    return ret;
}

V<SP<Stmt>> parser::parseStmtList() {
    V<SP<Stmt>> list;
    while (tok_ != token_type::CASE && tok_ != token_type::DEFAULT && tok_ != token_type::RBRACE &&
           tok_ != token_type::EOF_) {
        auto stmt = parseStmt();
        list.push_back(stmt);
    }
    return list;
}

SP<BlockStmt> parser::parseBody() {
    pos_t lbrace = expect(token_type::LBRACE);
    auto list = parseStmtList();
    pos_t rbrace = expect2(token_type::RBRACE);
    return std::make_shared<BlockStmt>(lbrace, list, rbrace);
}

SP<BlockStmt> parser::parseBlockStmt() {
    pos_t lbrace = expect(token_type::LBRACE);
    auto list = parseStmtList();
    pos_t rbrace = expect2(token_type::RBRACE);
    return std::make_shared<BlockStmt>(lbrace, list, rbrace);
}

SP<Expr> parser::parseFuncTypeOrLit() {
    auto typ = parseFuncType();
    if (tok_ != token_type::LBRACE) {
        return typ;
    }

    exprLev_++;
    auto body = parseBody();
    exprLev_--;
    SP<Expr> aa = std::make_shared<FuncLitExpr>(typ, body);
    return std::make_shared<FuncLitExpr>(typ, body);
}

SP<Expr> parser::parseOperand() {
    switch (tok_) {
        case token_type::IDENT: {
            auto x = parseIdent();
            return x;
        }
        case token_type::INT:
        case token_type::FLOAT:
        case token_type::CHAR:
        case token_type::IMAG:
        case token_type::STRING: {
            auto x = std::make_shared<BasicLitExpr>(pos_, tok_, lit_);
            next();
            return x;
        }

        case token_type::LPAREN: {
            pos_t lparen = pos_;
            next();
            exprLev_++;
            auto x = parseRhs();
            exprLev_--;
            pos_t rparen = expect(token_type::RPAREN);
            return std::make_shared<ParenExpr>(lparen, x, rparen);
        }
        case token_type::FUNC:
            return parseFuncTypeOrLit();
        default:
            break;
    }

    if (auto typ = tryIdentOrType(); typ != nullptr) {
        bool isIdent = dynamic_cast<IdentExpr*>(typ.get()) != nullptr;
        assert(!isIdent, "type cannot be identifier");
        return typ;
    }

    pos_t pos = pos_;
    errorExpected(pos, "operand");
    advance(stmtStart);
    return std::make_shared<BadExpr>(pos, pos_);
}

SP<Expr> parser::parseSelector(SP<Expr> x) {
    auto sel = parseIdent();
    return std::make_shared<SelectorExpr>(x, sel);
}

SP<Expr> parser::parseTypeAssertion(SP<Expr> x) {
    pos_t lparen = expect(token_type::LPAREN);
    SP<Expr> typ;
    if (tok_ == token_type::TYPE) {
        next();
    } else {
        typ = parseType();
    }
    pos_t rparen = expect(token_type::RPAREN);

    return std::make_shared<TypeAssertExpr>(x, typ, lparen, rparen);
}

SP<Expr> parser::parseIndexOrSliceOrInstance(SP<Expr> x) {
    pos_t lbrack = expect(token_type::LBRACK);
    if (tok_ == token_type::RBRACK) {
        errorExpected(pos_, "operand");
        pos_t rbrack = pos_;
        next();
        return std::make_shared<IndexExpr>(x, lbrack, std::make_shared<BadExpr>(rbrack, rbrack),
                                           rbrack);
    }
    exprLev_++;

    const int N = 3;
    V<SP<Expr>> args;
    SP<Expr> index[N];
    pos_t colons[N - 1];
    if (tok_ != token_type::COLON) {
        index[0] = parseRhs();
    }

    int ncolons = 0;
    switch (tok_) {
        case token_type::COLON: {
            while (tok_ == token_type::COLON && ncolons < (N - 1)) {
                colons[ncolons] = pos_;
                ncolons++;
                next();
                if (tok_ != token_type::COLON && tok_ != token_type::RBRACK &&
                    tok_ != token_type::EOF_) {
                    index[ncolons] = parseRhs();
                }
            }
            break;
        }
        case token_type::COMMA: {
            args.push_back(index[0]);
            while (tok_ == token_type::COMMA) {
                next();
                if (tok_ != token_type::RBRACK && tok_ != token_type::EOF_) {
                    args.push_back(parseType());
                }
            }
            break;
        }
        default:
            break;
    }

    exprLev_--;
    pos_t rbrack = expect(token_type::RBRACK);

    if (ncolons > 0) {
        bool slice3 = false;
        if (ncolons == 2) {
            slice3 = true;
            if (index[1] == nullptr) {
                error(colons[0], "middle index required in 3-index slice");
                index[1] = std::make_shared<BadExpr>(colons[0], colons[1]);
            }
            if (index[2] == nullptr) {
                error(colons[1], "final index required in 3-index slice");
                index[1] = std::make_shared<BadExpr>(colons[1], rbrack);
            }
        }
        return std::make_shared<SliceExpr>(x, lbrack, index[0], index[1], index[2], slice3, rbrack);
    }

    if (args.size() == 0) {
        return std::make_shared<IndexExpr>(x, lbrack, index[0], rbrack);
    }

    return packIndexExpr(x, lbrack, args, rbrack);
}

SP<CallExpr> parser::parseCallOrConversion(SP<Expr> fun) {
    pos_t lparen = expect(token_type::LPAREN);
    exprLev_++;
    V<SP<Expr>> list;
    pos_t ellipsis;
    while (tok_ != token_type::RPAREN && tok_ != token_type::EOF_ && !ellipsis.IsValid()) {
        list.push_back(parseRhs());
        if (tok_ == token_type::ELLIPSIS) {
            ellipsis = pos_;
            next();
        }
        if (!atComma("argument list", token_type::RPAREN)) {
            break;
        }
        next();
    }
    exprLev_--;
    pos_t rparen = expectClosing(token_type::RPAREN, "argument list");

    return std::make_shared<CallExpr>(fun, lparen, list, ellipsis, rparen);
}

SP<Expr> parser::parseValue() {
    if (tok_ == token_type::LBRACE) {
        return parseLiteralValue(nullptr);
    }

    auto x = parseExpr();
    return x;
}

SP<Expr> parser::parseElement() {
    auto x = parseValue();

    if (tok_ == token_type::COLON) {
        pos_t colon = pos_;
        next();
        x = std::make_shared<KeyValueExpr>(x, colon, parseValue());
    }

    return x;
}

V<SP<Expr>> parser::parseElementList() {
    V<SP<Expr>> list;
    while (tok_ != token_type::RBRACE && tok_ != token_type::EOF_) {
        list.push_back(parseElement());
        if (!atComma("composite literal", token_type::RBRACE)) {
            break;
        }
        next();
    }
    return list;
}

SP<Expr> parser::parseLiteralValue(SP<Expr> typ) {
    pos_t lbrace = expect(token_type::LBRACE);
    V<SP<Expr>> elts;
    exprLev_++;
    if (tok_ != token_type::RBRACE) {
        elts = parseElementList();
    }
    exprLev_--;
    pos_t rbrace = expectClosing(token_type::RBRACE, "composite literal");
    return std::make_shared<CompositeLitExpr>(typ, lbrace, elts, rbrace);
}

SP<Expr> parser::unparen(SP<Expr> x) {
    auto pair = isOfType<ParenExpr>(x.get());
    if (pair.second) {
        x = unparen(pair.first->X);
    }
    return x;
}

SP<Expr> parser::parsePrimaryExpr(SP<Expr> x) {
    if (x == nullptr) {
        x = parseOperand();
    }
    int n;
    for (n = 1;; n++) {
        incNestLev();
        switch (tok_) {
            case token_type::PERIOD: {
                next();
                switch (tok_) {
                    case token_type::IDENT: {
                        x = parseSelector(x);
                        break;
                    }
                    case token_type::LPAREN: {
                        x = parseTypeAssertion(x);
                        break;
                    }
                    default: {
                        pos_t pos = pos_;
                        errorExpected(pos, "selector or type assertion");
                        if (tok_ != token_type::RBRACE) {
                            next();
                        }
                        auto sel = IdentExpr(pos, "_");
                        x = std::make_shared<SelectorExpr>(x, std::make_shared<IdentExpr>(sel));
                        break;
                    }
                }
                break;
            }
            case token_type::LBRACK: {
                x = parseIndexOrSliceOrInstance(x);
                break;
            }
            case token_type::LPAREN: {
                x = parseCallOrConversion(x);
                break;
            }
            case token_type::LBRACE: {
                auto t = unparen(x);
                if (isOfType<BadExpr>(x.get()).second || isOfType<IdentExpr>(x.get()).second ||
                    isOfType<SelectorExpr>(x.get()).second) {
                    if (exprLev_ < 0) {
                        nestLev_ -= n;
                        return x;
                    }
                } else if (isOfType<IndexExpr>(x.get()).second ||
                           isOfType<IndexListExpr>(x.get()).second) {
                    if (exprLev_ < 0) {
                        nestLev_ -= n;
                        return x;
                    }
                } else if (isOfType<ArrayTypeExpr>(x.get()).second ||
                           isOfType<StructTypeExpr>(x.get()).second ||
                           isOfType<MapTypeExpr>(x.get()).second) {
                } else {
                    nestLev_ -= n;
                    return x;
                }
                if ((!t && x) || !(!t && !x) && *t != *x) {
                    error(t->Pos(), "cannot parenthesize type in composite literal");
                }
                x = parseLiteralValue(x);
                break;
            }
            default:
                nestLev_ -= n;
                return x;
                break;
        }
    }
}

SP<Expr> parser::parseUnaryExpr() {
    incNestLev();
    switch (tok_) {
        case token_type::ADD:
        case token_type::SUB:
        case token_type::NOT:
        case token_type::XOR:
        case token_type::AND:
        case token_type::TILDE: {
            pos_t pos = pos_;
            auto op = tok_;
            next();
            auto x = parseUnaryExpr();
            decNestLev();
            return std::make_shared<UnaryExpr>(pos, op, x);
        }
        case token_type::MUL: {
            pos_t pos = pos_;
            next();
            auto x = parseUnaryExpr();
            decNestLev();
            return std::make_shared<StarExpr>(pos, x);
        }
        default:
            break;
    }
    auto ret = parsePrimaryExpr(nullptr);
    decNestLev();
    return ret;
}

std::pair<token_type, int> parser::tokPrec() {
    auto tok = tok_;
    if (inRhs_ && tok == token_type::ASSIGN) {
        tok = token_type::EQL;
    }
    return {tok, Precedence(tok)};
}

SP<Expr> parser::parseBinaryExpr(SP<Expr> x, int prec1) {
    if (x == nullptr) {
        x = parseUnaryExpr();
    }
    int n = 0;
    for (n = 1;; n++) {
        incNestLev();
        token_type op;
        int oprec;
        std::tie(op, oprec) = tokPrec();
        if (oprec < prec1) {
            nestLev_ -= n;
            return x;
        }
        pos_t pos = expect(op);
        auto y = parseBinaryExpr(nullptr, oprec + 1);
        x = std::make_shared<BinaryExpr>(x, pos, op, y);
    }
}

SP<Expr> parser::parseExpr() { return parseBinaryExpr(nullptr, LowestPrec + 1); }

SP<Expr> parser::parseRhs() {
    bool old = inRhs_;
    inRhs_ = true;
    auto x = parseExpr();
    inRhs_ = old;
    return x;
}

const int basic = 0;
const int labelOk = 1;
const int rangeOk = 2;

std::pair<SP<Stmt>, bool> parser::parseSimpleStmt(int mode) {
    auto x = parseList(false);
    switch (tok_) {
        case token_type::DEFINE:
        case token_type::ASSIGN:
        case token_type::ADD_ASSIGN:
        case token_type::SUB_ASSIGN:
        case token_type::MUL_ASSIGN:
        case token_type::QUO_ASSIGN:
        case token_type::REM_ASSIGN:
        case token_type::AND_ASSIGN:
        case token_type::OR_ASSIGN:
        case token_type::XOR_ASSIGN:
        case token_type::SHL_ASSIGN:
        case token_type::SHR_ASSIGN:
        case token_type::AND_NOT_ASSIGN: {
            pos_t pos = pos_;
            token_type tok = tok_;
            next();
            V<SP<Expr>> y;
            bool isRange = false;
            if (mode == rangeOk && tok_ == token_type::RANGE &&
                (tok == token_type::DEFINE || tok == token_type::ASSIGN)) {
                pos_t pos = pos_;
                next();
                y = {std::make_shared<UnaryExpr>(pos, token_type::RANGE, parseRhs())};
                isRange = true;
            } else {
                y = parseList(true);
            }
            return {std::make_shared<AssignStmt>(x, pos, tok, y), isRange};
        }
    }

    if (x.size() > 1) {
        errorExpected(x[0]->Pos(), "1 expression");
    }

    switch (tok_) {
        case token_type::COLON: {
            pos_t colon = pos_;
            next();
            if (auto [label, isIdent] = isOfType<IdentExpr>(x[0].get());
                mode == labelOk && isIdent) {
                auto stmt = std::make_shared<LabeledStmt>(std::make_shared<IdentExpr>(*label),
                                                          colon, parseStmt());
                return {stmt, false};
            }
            error(colon, "illegal label declaration");
            return {std::make_shared<BadStmt>(x[0]->Pos(), colon), false};
        }
        case token_type::INC:
        case token_type::DEC: {
            auto s = std::make_shared<IncDecStmt>(x[0], pos_, tok_);
            next();
            return {s, false};
        }
    }

    return {std::make_shared<ExprStmt>(x[0]), false};
}

SP<CallExpr> parser::parseCallExpr(std::string callType) {
    auto x = parseRhs();
    if (auto t = unparen(x); (!t && x) || !(!t && !x) && *t != *x) {
        error(x->Pos(), "expression in" + callType + "must not be parenthesized");
        x = t;
    }
    if (auto [call, isCall] = isOfType<CallExpr>(x.get()); isCall) {
        return std::make_shared<CallExpr>(*call);
    }
    if (auto [_, isBad] = isOfType<BadExpr>(x.get()); !isBad) {
        error(x->Pos(), "expression in" + callType + "must be function call");
    }
    return nullptr;
}

// TODO parse go

SP<Stmt> parser::parseDeferStmt() {
    pos_t pos = expect(token_type::DEFER);
    auto call = parseCallExpr("defer");
    expectSemi();
    if (call == nullptr) {
        return std::make_shared<BadStmt>(pos, pos + 5);
    }

    return std::make_shared<DeferStmt>(pos, call);
}

SP<ReturnStmt> parser::parseReturnStmt() {
    pos_t pos = pos_;
    expect(token_type::RETURN);
    V<SP<Expr>> x;
    if (tok_ != token_type::SEMICOLON && tok_ != token_type::RBRACE) {
        x = parseList(true);
    }
    expectSemi();
    return std::make_shared<ReturnStmt>(pos, x);
}

SP<BranchStmt> parser::parseBranchStmt(token_type tok) {
    pos_t pos = expect(tok);
    SP<IdentExpr> label;
    if (tok != token_type::FALLTHROUGH && tok_ == token_type::IDENT) {
        label = parseIdent();
    }
    expectSemi();
    return std::make_shared<BranchStmt>(pos, tok, label);
}

SP<Expr> parser::makeExpr(SP<Stmt> s, std::string want) {
    if (s == nullptr) {
        return nullptr;
    }
    if (auto [es, isExpr] = isOfType<ExprStmt>(s.get()); isExpr) {
        return es->X;
    }
    std::string found = "simple statement";
    if (auto [_, isAss] = isOfType<AssignStmt>(s.get()); isAss) {
        found = "assignment";
    }
    error(s->Pos(), "expected " + want + ", found " + found +
                        " (missing parentheses around composite literal?)");
    return std::make_shared<BadExpr>(s->Pos(), s->End());
}

std::pair<SP<Stmt>, SP<Expr>> parser::parseIfHeader() {
    SP<Stmt> init;
    SP<Expr> cond;
    if (tok_ == token_type::LBRACE) {
        error(pos_, "missing condition in if statement");
        cond = std::make_shared<BadExpr>(pos_, pos_);
        return {init, cond};
    }

    int prevLev = exprLev_;
    exprLev_ = -1;

    if (tok_ != token_type::SEMICOLON) {
        if (tok_ == token_type::VAR) {
            next();
            error(pos_, "var declaration not allowed in if initializer");
        }
        init = parseSimpleStmt(basic).first;
    }

    SP<Stmt> condStmt;
    struct semi {
        pos_t pos;
        std::string lit;
    };
    semi semi;
    if (tok_ != token_type::LBRACE) {
        if (tok_ == token_type::SEMICOLON) {
            semi.pos = pos_;
            semi.lit = lit_;
            next();
        } else {
            expect(token_type::SEMICOLON);
        }
        if (tok_ != token_type::LBRACE) {
            condStmt = parseSimpleStmt(basic).first;
        }
    } else {
        condStmt = init;
        init = nullptr;
    }

    if (condStmt != nullptr) {
        cond = makeExpr(condStmt, "boolean expression");
    } else if (semi.pos.IsValid()) {
        if (semi.lit == "\n") {
            error(semi.pos, "unexpected newline, expecting { after if clause");
        } else {
            error(semi.pos, "missing condition in if statement");
        }
    }

    if (cond == nullptr) {
        cond = std::make_shared<BadExpr>(pos_, pos_);
    }

    exprLev_ = prevLev;
    return {init, cond};
}

SP<IfStmt> parser::parseIfStmt() {
    incNestLev();
    pos_t pos = expect(token_type::IF);
    auto [init, cond] = parseIfHeader();
    auto body = parseBlockStmt();

    SP<Stmt> else_;
    if (tok_ == token_type::ELSE) {
        next();
        switch (tok_) {
            case token_type::IF:
                else_ = parseIfStmt();
                break;
            case token_type::LBRACE:
                else_ = parseBlockStmt();
                expectSemi();
                break;
            default:
                errorExpected(pos_, "if statement or block");
                else_ = std::make_shared<BadStmt>(pos_, pos_);
                break;
        }
    } else {
        expectSemi();
    }
    decNestLev();

    return std::make_shared<IfStmt>(pos, init, cond, body, else_);
}

SP<CaseClauseStmt> parser::parseCaseClause() {
    pos_t pos = pos_;
    V<SP<Expr>> list;
    if (tok_ == token_type::CASE) {
        next();
        list = parseList(true);
    } else {
        expect(token_type::DEFAULT);
    }

    pos_t colon = expect(token_type::COLON);
    auto body = parseStmtList();

    return std::make_shared<CaseClauseStmt>(pos, list, colon, body);
}

bool isTypeSwitchAssert(SP<Expr> x) {
    auto [a, ok] = isOfType<TypeAssertExpr>(x.get());
    return ok && a->Type == nullptr;
}

bool parser::isTypeSwitchGuard(SP<Stmt> s) {
    if (auto [t, ok] = isOfType<ExprStmt>(s.get()); ok) {
        return isTypeSwitchAssert(t->X);
    } else if (auto [t, ok] = isOfType<AssignStmt>(s.get()); ok) {
        if (t->Lhs.size() == 1 && t->Rhs.size() == 1 && isTypeSwitchAssert(t->Rhs[0])) {
            switch (t->Tok) {
                case token_type::ASSIGN:
                    error(t->TokPos, "expected ':=', found '='");
                // no break intentionally
                case token_type::DEFINE:
                    return true;
            }
        }
    }
    return false;
}

SP<Stmt> parser::parseSwitchStmt() {
    pos_t pos = expect(token_type::SWITCH);
    SP<Stmt> s1, s2;
    if (tok_ != token_type::LBRACE) {
        int prevLev = exprLev_;
        exprLev_ = -1;
        if (tok_ != token_type::SEMICOLON) {
            s2 = parseSimpleStmt(basic).first;
        }
        if (tok_ == token_type::SEMICOLON) {
            next();
            s1 = s2;
            s2 = nullptr;
            if (tok_ != token_type::LBRACE) {
                s2 = parseSimpleStmt(basic).first;
            }
        }
        exprLev_ = prevLev;
    }

    bool typeSwitch = isTypeSwitchGuard(s2);
    pos_t lbrace = expect(token_type::LBRACE);
    V<SP<Stmt>> list;
    while (tok_ == token_type::CASE || tok_ == token_type::DEFAULT) {
        list.push_back(parseCaseClause());
    }
    pos_t rbrace = expect(token_type::RBRACE);
    expectSemi();
    auto body = std::make_shared<BlockStmt>(lbrace, list, rbrace);

    if (typeSwitch) {
        return std::make_shared<TypeSwitchStmt>(pos, s1, s2, body);
    }

    return std::make_shared<SwitchStmt>(pos, s1, makeExpr(s2, "switch expression"), body);
}

SP<Stmt> parser::parseForStmt() {
    pos_t pos = expect(token_type::FOR);

    SP<Stmt> s1, s2, s3;
    bool isRange = false;

    if (tok_ != token_type::LBRACE) {
        int prevLev = exprLev_;
        exprLev_ = -1;
        if (tok_ != token_type::SEMICOLON) {
            if (tok_ == token_type::RANGE) {
                pos_t pos = pos_;
                next();
                V<SP<Expr>> y = {std::make_shared<UnaryExpr>(pos, token_type::RANGE, parseRhs())};
                s2 = std::make_shared<AssignStmt>(V<SP<Expr>>{}, NoPos, token_type(), y);
                isRange = true;
            } else {
                std::tie(s2, isRange) = parseSimpleStmt(rangeOk);
            }
        }
        if (!isRange && tok_ == token_type::SEMICOLON) {
            next();
            s1 = s2;
            s2 = nullptr;
            if (tok_ != token_type::SEMICOLON) {
                s2 = parseSimpleStmt(basic).first;
            }
            expectSemi();
            if (tok_ != token_type::LBRACE) {
                s3 = parseSimpleStmt(basic).first;
            }
        }
        exprLev_ = prevLev;
    }

    auto body = parseBlockStmt();
    expectSemi();

    if (isRange) {
        auto as = isOfType<AssignStmt>(s2.get()).first;
        SP<Expr> key, value;
        switch (as->Lhs.size()) {
            case 0:
                break;
            case 1: {
                key = as->Lhs[0];
                break;
            }
            case 2: {
                key = as->Lhs[0];
                value = as->Lhs[1];
                break;
            }
            default:
                errorExpected(as->Lhs[as->Lhs.size() - 1]->Pos(), "at most 2 expressions");
                return std::make_shared<BadStmt>(pos, body->End());
        }

        auto x = isOfType<UnaryExpr>(as->Rhs[0].get()).first->X;
        return std::make_shared<RangeStmt>(pos, key, value, as->TokPos, as->Tok, as->Rhs[0]->Pos(),
                                           x, body);
    }

    auto madeExpr = makeExpr(s2, "boolean or range expression");
    return std::make_shared<ForStmt>(pos, s1, madeExpr, s3, body);
}

SP<Stmt> parser::parseStmt() {
    incNestLev();
    SP<Stmt> s;
    switch (tok_) {
        case token_type::CONST:
        case token_type::TYPE:
        case token_type::VAR: {
            s = std::make_shared<DeclStmt>(parseDecl(stmtStart));
            break;
        }

        case token_type::IDENT:
        case token_type::INT:
        case token_type::FLOAT:
        case token_type::IMAG:
        case token_type::CHAR:
        case token_type::STRING:
        case token_type::FUNC:
        case token_type::LPAREN:
        case token_type::LBRACK:
        case token_type::STRUCT:
        case token_type::MAP:
        case token_type::INTERFACE:
        case token_type::ADD:
        case token_type::SUB:
        case token_type::MUL:
        case token_type::AND:
        case token_type::XOR:
        case token_type::NOT: {
            s = parseSimpleStmt(labelOk).first;
            if (auto [_, isLabeledStmt] = isOfType<LabeledStmt>(s.get()); !isLabeledStmt) {
                expectSemi();
            }
            break;
        }
        case token_type::DEFER:
            s = parseDeferStmt();
            break;
        case token_type::RETURN:
            s = parseReturnStmt();
            break;
        case token_type::BREAK:
        case token_type::CONTINUE:
        case token_type::GOTO:
        case token_type::FALLTHROUGH:
            s = parseBranchStmt(tok_);
            break;
        case token_type::LBRACE:
            s = parseBlockStmt();
            expectSemi();
            break;
        case token_type::IF:
            s = parseIfStmt();
            break;
        case token_type::SWITCH:
            s = parseSwitchStmt();
            break;
        case token_type::FOR:
            s = parseForStmt();
            break;
        case token_type::SEMICOLON:
            s = std::make_shared<EmptyStmt>(pos_, (lit_ == "\n"));
            next();
            break;

        case token_type::RBRACE:
            s = std::make_shared<EmptyStmt>(pos_, true);
            break;
        default:
            pos_t pos = pos_;
            errorExpected(pos, "statement");
            advance(stmtStart);
            s = std::make_shared<BadStmt>(pos, pos_);
            break;
    }

    decNestLev();
    return s;
}

SP<Spec> parser::parseImportSpec(token_type _, int __) {
    SP<IdentExpr> ident;
    switch (tok_) {
        case token_type::IDENT:
            ident = parseIdent();
            break;
        case token_type::PERIOD:
            ident = std::make_shared<IdentExpr>(pos_, ".");
            next();
    }

    pos_t pos = pos_;
    std::string path;
    if (tok_ == token_type::STRING) {
        path = lit_;
        next();
    } else if (is_literal(tok_)) {
        error(pos, "import path must be a string");
        next();
    } else {
        error(pos, "missing import path");
        advance(exprEnd);
    }
    expectSemi();

    auto spec = std::make_shared<ImportSpec>(
        ident, std::make_shared<BasicLitExpr>(pos, token_type::STRING, path), NoPos);

    return spec;
}

SP<Spec> parser::parseValueSpec(token_type keyword, int iota) {
    auto idents = parseIdentList();
    SP<Expr> typ;
    V<SP<Expr>> values;
    switch (keyword) {
        case token_type::CONST:
            if (tok_ != token_type::EOF_ && tok_ != token_type::SEMICOLON &&
                tok_ != token_type::RPAREN) {
                typ = tryIdentOrType();
                if (tok_ == token_type::ASSIGN) {
                    next();
                    values = parseList(true);
                }
            }
            break;

        case token_type::VAR:
            if (tok_ != token_type::ASSIGN) {
                typ = parseType();
            }
            if (tok_ == token_type::ASSIGN) {
                next();
                values = parseList(true);
            }
            break;
        default:
            throw std::runtime_error("unreachable");
            break;
    }
    expectSemi();

    auto spec = std::make_shared<ValueSpec>(idents, typ, values);
    return spec;
}

void parser::parseGenericType(SP<TypeSpec> spec, pos_t openPos, SP<IdentExpr> name0,
                              SP<Expr> typ0) {
    auto list = parseParameterList(name0, typ0, token_type::RBRACK);
    pos_t closePos = expect(token_type::RBRACK);
    spec->TypeParams = std::make_shared<FieldList>(openPos, list, closePos);

    if (tok_ == token_type::ASSIGN) {
        spec->Assign = pos_;
        next();
    }
    spec->Type = parseType();
}

bool isTypeElem(SP<Expr> x) {
    if (isOfType<ArrayTypeExpr>(x.get()).second || isOfType<StructTypeExpr>(x.get()).second ||
        isOfType<FuncTypeExpr>(x.get()).second || isOfType<InterfaceTypeExpr>(x.get()).second ||
        isOfType<MapTypeExpr>(x.get()).second) {
        return true;
    } else if (auto [ptr, is] = isOfType<BinaryExpr>(x.get()); is) {
        return isTypeElem(ptr->X) || isTypeElem(ptr->Y);
    } else if (auto [ptr, is] = isOfType<UnaryExpr>(x.get()); is) {
        return ptr->Op == token_type::TILDE;
    } else if (auto [ptr, is] = isOfType<ParenExpr>(x.get()); is) {
        return isTypeElem(ptr->X);
    }
    return false;
}

std::pair<SP<IdentExpr>, SP<Expr>> extractName(SP<Expr> x, bool force) {
    if (auto [ptr, is] = isOfType<IdentExpr>(x.get()); is) {
        return {std::make_shared<IdentExpr>(*ptr), nullptr};
    } else if (auto [ptr, is] = isOfType<BinaryExpr>(x.get()); is) {
        switch (ptr->Op) {
            case token_type::MUL:
                if (auto [name, _] = isOfType<IdentExpr>(ptr->X.get());
                    name != nullptr && (force || isTypeElem(ptr->Y))) {
                    return {std::make_shared<IdentExpr>(*name),
                            std::make_shared<StarExpr>(ptr->OpPos, ptr->Y)};
                }
                break;
            case token_type::OR:
                if (auto [name, lhs] = extractName(ptr->X, force || isTypeElem(ptr->Y));
                    name != nullptr && lhs != nullptr) {
                    auto op = *ptr;
                    op.X = lhs;
                    return {name, std::make_shared<BinaryExpr>(op)};
                }
                break;
        }
    } else if (auto [ptr, is] = isOfType<CallExpr>(x.get()); is) {
        if (auto [name, _] = isOfType<IdentExpr>(ptr->Fun.get()); name != nullptr) {
            if (ptr->Args.size() == 1 && ptr->Ellipsis == NoPos &&
                (force || isTypeElem(ptr->Args[0]))) {
                return {std::make_shared<IdentExpr>(*name), ptr->Args[0]};
            }
        }
    }
    return {nullptr, x};
}

SP<Spec> parser::parseTypeSpec(token_type _, int __) {
    auto name = parseIdent();
    auto spec = std::make_shared<TypeSpec>(name, nullptr, NoPos, nullptr);

    if (tok_ == token_type::LBRACK) {
        pos_t lbrack = pos_;
        next();
        if (tok_ == token_type::IDENT) {
            SP<Expr> x = parseIdent();
            if (tok_ != token_type::LBRACK) {
                exprLev_++;
                auto lhs = parsePrimaryExpr(x);
                x = parseBinaryExpr(lhs, LowestPrec + 1);
                exprLev_--;
            }
            if (auto [pname, ptype] = extractName(x, tok_ == token_type::COMMA);
                pname != nullptr && (ptype != nullptr || tok_ != token_type::RBRACK)) {
                parseGenericType(spec, lbrack, pname, ptype);
            } else {
                spec->Type = parseArrayType(lbrack, x);
            }
        } else {
            spec->Type = parseArrayType(lbrack, nullptr);
        }
    } else {
        if (tok_ == token_type::ASSIGN) {
            spec->Assign = pos_;
            next();
        }
        spec->Type = parseType();
    }

    expectSemi();
    return spec;
}

SP<GenDecl> parser::parseGenDecl(token_type keyword, parseSpecFunction f) {
    pos_t pos = expect(keyword);

    pos_t lparen, rparen;
    V<SP<Spec>> list;
    if (tok_ == token_type::LPAREN) {
        lparen = pos_;
        next();
        for (int iota = 0; tok_ != token_type::RPAREN && tok_ != token_type::EOF_; iota++) {
            list.push_back(f(keyword, iota));
        }
        rparen = expect(token_type::RPAREN);
        expectSemi();
    } else {
        list.push_back(f(keyword, 0));
    }

    return std::make_shared<GenDecl>(pos, keyword, lparen, list, rparen);
}

SP<FuncDecl> parser::parseFuncDecl() {
    pos_t pos = expect(token_type::FUNC);

    SP<FieldList> recv;
    if (tok_ == token_type::LPAREN) {
        recv = parseParameters(false).second;
    }

    auto ident = parseIdent();

    auto [tparams, params] = parseParameters(true);
    if (recv != nullptr && tparams != nullptr) {
        error(tparams->Opening, "method must have no type parameters");
        tparams = nullptr;
    }
    auto results = parseResult();

    SP<BlockStmt> body;
    switch (tok_) {
        case token_type::LBRACE:
            body = parseBody();
            expectSemi();
            break;

        case token_type::SEMICOLON:
            next();
            if (tok_ == token_type::LBRACE) {
                error(pos_, "unexpected semicolon or newline before {");
                body = parseBody();
                expectSemi();
            }
            break;

        default:
            expectSemi();
            break;
    }

    auto decl = std::make_shared<FuncDecl>(
        recv, ident, std::make_shared<FuncTypeExpr>(pos, tparams, params, results), body);
    return decl;
}

SP<Decl> parser::parseDecl(std::unordered_map<token_type, bool> sync) {
    parseSpecFunction f;
    switch (tok_) {
        case token_type::IMPORT:
            f = std::bind(&parser::parseImportSpec, this, std::placeholders::_1,
                          std::placeholders::_2);
            break;

        case token_type::CONST:
        case token_type::VAR:
            f = std::bind(&parser::parseValueSpec, this, std::placeholders::_1,
                          std::placeholders::_2);
            break;

        case token_type::TYPE:
            f = std::bind(&parser::parseTypeSpec, this, std::placeholders::_1,
                          std::placeholders::_2);
            break;

        case token_type::FUNC:
            return parseFuncDecl();
        default:
            pos_t pos = pos_;
            errorExpected(pos, "declaration");
            advance(sync);
            return std::make_shared<BadDecl>(pos, pos_);
    }

    return parseGenDecl(tok_, f);
}

void parser::printErrors() const {
    std::cout << '\n';
    for (const auto& e : errors_) {
        std::cout << color::error << "Error at " << color::reset << e.pos.line << ':' << e.pos.col
                  << " --- " << e.msg << '\n';
    }
    std::cout << '\n';
}

void parser::parseFile() {
    if (!errors_.empty()) {
        return;
    }

    pos_t pos = expect(token_type::PACKAGE);
    auto ident = parseIdent();
    if (ident->Name == "_") {
        error(pos_, "invalid package name _");
    }

    expectSemi();

    if (!errors_.empty()) {
        return;
    }

    while (tok_ == token_type::IMPORT) {
        decls_.push_back(parseGenDecl(
            token_type::IMPORT, std::bind(&parser::parseImportSpec, this, std::placeholders::_1,
                                          std::placeholders::_2)));
    }

    auto prev = token_type::IMPORT;
    while (tok_ != token_type::EOF_) {
        if (tok_ == token_type::IMPORT && prev != token_type::IMPORT) {
            error(pos_, "imports must appear before other declarations");
        }
        prev = tok_;
        decls_.push_back(parseDecl(declStart));
    }

    printErrors();
}