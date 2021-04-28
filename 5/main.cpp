#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <string>

using namespace std;

// struct tree
// {
//     map<int, tree *> to;
//     tree *link;
// };

// void bfs(tree *root) {
//     queue<tree*> q;
//     // сразу проставим ссылку корню и его детям
//     root->link = root;
//     for (auto pair : root->to) {
//         pair.second->link = root;
//         // запушим детей в очередь, чтобы начать со второго слоя бора
//         q.push(pair.second);
//     }
//     // идём обычным бфсом
//     while (!q.empty()) {
//         // достали вершину
//         auto v = q.front();
//         q.pop();
//         // обойдём всех потомков, для которых есть переход в боре
//         for (auto pair : v->to) {
//             int parent_char = pair.first;
//             tree *child = pair.second;
//             tree *parent_suffix = v->link; // нашли максимальный суффикс родителя
//             tree *next_suffix = parent_suffix->to[parent_char]; // нашли переход из суффикса родителя по заданному символу
//             child->link = next_suffix; // присвоили это значение ребёнку
//             q.push(child); // запушили ребёнка в очередь
//         }
//     }
// }

class Aho
{
    struct tree
    {
        map<char, struct tree *> to;
        vector<string> out;
        struct tree *fail = nullptr;
    };
    Aho()
    {
        
    }
    ~Aho()
    {
    }
    void add(vector<string> patterns)
    {
        struct tree *root = (struct tree *)malloc(sizeof(struct tree));
        for (auto path : patterns)
        {
            struct tree *node = root;
            cout << "CREATED BOR\n";
            for (auto symbol : path)
                node->to[symbol] = (struct tree *)malloc(sizeof(struct tree));
            node->out.push_back(path);
        }

        queue<struct tree *> q;
        for (auto const &x : root->to)
        {
            q.push(x.second);
            x.second->fail = root;
        }
        while (!q.empty())
        {
            struct tree *rnode = q.front();
            q.pop();

            for (auto const &x : rnode->to)
            {
                q.push(x.second);
                struct tree *fnode = rnode->fail;
                while (fnode != nullptr && fnode->to.find(x.first) == fnode->to.end())
                    fnode = fnode->fail;
                x.second->fail = (fnode) ? fnode->to[x.first] : root;
                x.second->out.insert(x.second->out.end(), x.second->fail->out.begin(), x.second->fail->out.end());
            }
        }
    }
    void find_all(string s, struct tree *root)
    {
        struct tree *node = root;

        for (int i = 0; i < s.size(); i++)
        {
            while (node != nullptr && node->to.find(s[i]) == node->to.end())
                node = node->fail;
            if (node != nullptr)
            {
                node = root;
                continue;
            }
            node = node->to[s[i]];
            for (auto pattern : node->out)
                cout << "At pos " << i - pattern.size() << " found pattern: " << pattern << endl;
        }
    }
};

int main(int argc, char **argv)
{
    if (argc < 3)
        return -1;

    ifstream inp(argv[1]);

    vector<string> patterns;
    int n;
    string temp, text;
    inp >> n;
    for (int i = 0; i < n; i++)
    {
        inp >> temp;
        patterns.push_back(temp);
    }

    inp >> text;

    struct tree *root = create_machine(patterns);
    find_all(text, root);

    ofstream out(argv[2], std::ios::out | std::ios::trunc);

    // out << ch.size() << endl;
    // for (int i = 0; i < ch.size(); i++)
    //     out << ch[i] << endl;

    out.close();
}