#include <treecode.hpp>

namespace treecode {
    class tmpl {
        tmpl(const std::string& name) : __name(name) {}
        public:
            void tmpl(const std::string& name) {
                /* throw exception in case the name is empty */
                if(name.empty()) Exception::Throw::Invalid(this->__name, "Name of the template can't be empty.");
                /* add the template to the list of templates */
                auto tmpl = std::make_shared<groupTemplate>(name);
                /* add the template to the list of templates */
                this->m_templates.emplace_back(tmpl);
            }



        private:
            std::string __name;
            std::vector<std::shared_ptr<groupTemplate>> m_templates;
    };
}