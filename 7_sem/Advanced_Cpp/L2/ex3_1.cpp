#include <iostream>
#include <string>
#include <memory>
#include <vector>
#include <set>

class llama : public std::enable_shared_from_this<llama> {
public:
    enum class gender { male, female };

private:
    std::string name;
    gender sex;
    std::shared_ptr<llama> father;
    std::shared_ptr<llama> mother;
    std::vector<std::weak_ptr<llama>> children;

public:
    static std::shared_ptr<llama> noname() {
        static std::shared_ptr<llama> inst = std::make_shared<llama>("noname", gender::male, nullptr, nullptr, false);
        return inst;
    }

    static std::shared_ptr<llama> create(std::string n, gender g,
                                         std::shared_ptr<llama> f = nullptr,
                                         std::shared_ptr<llama> m = nullptr)
    {
        auto obj = std::make_shared<llama>(std::move(n), g, f, m, /*register_with_parents=*/false);
        if (f && f != noname()) f->add_child(obj);
        if (m && m != noname()) m->add_child(obj);
        return obj;
    }

    llama(const std::string& n, gender g,
          std::shared_ptr<llama> f = nullptr,
          std::shared_ptr<llama> m = nullptr,
          bool register_with_parents = true)
        : name(n), sex(g),
          father(f ? f : nullptr),
          mother(m ? m : nullptr)
    {
        std::cout << "Lama " << name << " została stworzona. "
                  << "(płeć: " << (sex == gender::male ? "samiec" : "samica") << ")\n";

        if (register_with_parents) {
            if (father && father != noname())
                father->add_child(shared_from_this());
            if (mother && mother != noname())
                mother->add_child(shared_from_this());
        }
    }

    void add_child(std::shared_ptr<llama> child) {
        children.push_back(child);
    }

    std::string get_name() const { return name; }
    gender get_gender() const { return sex; }

    ~llama() {
        std::cout << "💀 Lama " << name << " odeszła.\n";
    }

    bool operator<(const llama& other) const {
        return name < other.name;
    }
};

class herd {
private:
    std::set<std::shared_ptr<llama>,
             bool(*)(const std::shared_ptr<llama>&, const std::shared_ptr<llama>&)> llamas;

    static bool compare(const std::shared_ptr<llama>& a, const std::shared_ptr<llama>& b) {
        return a->get_name() < b->get_name();
    }

public:
    herd() : llamas(compare) {}

    void buy_llama(const std::string& name, llama::gender g) {
        llamas.insert(llama::create(name, g, llama::noname(), llama::noname()));
    }

    void birth(const std::string& name,
               std::shared_ptr<llama> father,
               std::shared_ptr<llama> mother,
               llama::gender g)
    {
        llamas.insert(llama::create(name, g, father, mother));
    }

    std::shared_ptr<llama> find(const std::string& name) const {
        for (auto& l : llamas)
            if (l->get_name() == name)
                return l;
        return nullptr;
    }

    void show() const {
        std::cout << "\nStado lam:\n";
        for (auto& l : llamas)
            std::cout << "🐪 " << l->get_name() << "\n";
        std::cout << "*******************\n";
    }
};

int main() 
{
    herd h;

    h.buy_llama("Carlos", llama::gender::male);
    h.buy_llama("Luna", llama::gender::female);

    auto carlos = h.find("Carlos");
    auto luna = h.find("Luna");

    h.birth("Chico", carlos, luna, llama::gender::male);
    h.birth("Bella", carlos, luna, llama::gender::female);

    h.show(); 
}
