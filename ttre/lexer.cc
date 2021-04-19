#include <ttre/lexer.h>
#include <cctype>
#include <optional>

namespace TTre
{
    Lexer Lexer::operator++(int)
    {
        this->get_next_token();
        return *this;
    }
    Token Lexer::get_next_token()
    {
        TTre::Token::_enumerated token = Token::T_UNKNOWN;
        unsigned char read = static_cast<unsigned char>(this->source_[this->pointer_]);

        if (this->current_)
            this->last_ = this->current_;
        if (this->pointer_ >= this->source_.length())
        {
            this->current_ = Token::T_END;
            return Token::T_END;
        }

        switch (read)
        {
        case '*': token = Token::T_KLEENE_STAR;
            break;
        case '|': token = Token::T_UNION;
            break;
        case '(': token = Token::T_OPEN_PAREN;
            break;
        case ')': token = Token::T_CLOSE_PAREN;
            break;
        }

        if (std::isalpha(read))
            token = Token::T_CHAR;

        this->pointer_++;

        this->current_ = token;
        this->scanner_ = read;
        return token;
    }

} // namespace TTre