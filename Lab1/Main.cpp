/*Список программного обеспечения представлен в виде дерева. Внутренние узлы дерева представляют собой категории и подкатегории.
Листовые узлы соответствуют программному обеспечению. Каждому ПО сопоставлено ряд полей и флагов (поддерживается/не поддерживается,
свободное/платное, сайт производителя, последняя версия и т.д.). Написать программу, позволяющую выводить список программного обеспечения
определенной категории с заданными критериями (например, только свободное, или только то, которое имеет поддержку).*/

#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Node
{
    string name;              
    bool is_category;         
    bool is_supported;        
    bool is_free;             
    string website;           
    string latest_version;    
    vector<Node*> children;   
};

void PrintSofrware(Node* node, bool supported_only, bool free_only)
{
    if (node->is_category)
        for (Node* child : node->children)
            PrintSofrware(child, supported_only, free_only);
    else if ((!supported_only || node->is_supported) && (!free_only || node->is_free))
    {
        cout << "Name: " << node->name << endl << "Supported: " << (node->is_supported ? "Yes" : "No") << endl
            << "Free: " << (node->is_free ? "Yes" : "No") << endl << "Website: " << node->website << endl
            << "Latest version: " << node->latest_version << endl << endl;
    }
}

void DestructTree(Node* root)
{
    for (Node* child : root->children)
    {
        for (Node* grandchild : child->children)
            delete grandchild;
        delete child;
    }
    delete root;
}

int main()
{
    Node* root = new Node{ "Software", true, false, false, "", "",
        {new Node {"Security", true, false, false, "", "", {
            new Node {"Antivirus", true, false, false, "", "", {
                new Node {"Avast", false, true, true, "https://www.avast.com", "21.3.2459"},
                new Node {"Kaspersky", false, true, false, "https://www.kaspersky.com", "2021"},
                new Node {"Norton", false, true, false, "https://ru.norton.com", "22.20.5.39"}}},
            new Node {"Firewall", true, true, true, "", "", {
                new Node {"ZoneAlarm", false, true, false, "https://www.zonealarm.com", "15.8.163.18715"},
                new Node {"Comodo", false, true, true, "https://personalfirewall.comodo.com", "12.2.2.7036"}}}}},
        new Node {"Productivity", true, true, false, "", "", {
            new Node {"Office", true, false, false, "", "", {
                new Node {"Microsoft Office", false, true, false, "https://www.microsoft.com", "2021"},
                new Node {"LibreOffice", false, true, true, "https://www.libreoffice.org", "7.2.2"}}},
            new Node {"Graphics", true, true, true, "", "", {
                new Node {"Adobe Photoshop", false, true, false, "https://www.adobe.com/products/photoshop.html", "22.3.0"},
                new Node {"GIMP", false, true, true, "https://www.gimp.org", "2.10.28"}}}}},
        new Node {"Communication", true, true, true, "", "", {
            new Node {"Skype", false, true, false,"https://www.skype.com/", "8.79"},
            new Node {"Discord", false, true, true, "https://discord.com/", "172.24"}}},
        new Node {"Development", true, true, false, "", "", {
            new Node {"VisualStudio", false, true, false, "https://visualstudio.microsoft.com/", "2022"},
            new Node {"VSCode", false, true, false, "https://code.visualstudio.com/", "1.77"}}}}
    };

    cout << "Security software (supported and free):" << endl;
    PrintSofrware(root->children[0], true, true);

    cout << "Office software (supported only):" << endl;
    PrintSofrware(root->children[1]->children[0], true, false);

    cout << "Communication software (free only)" << endl;
    PrintSofrware(root->children[2], false, true);

    cout << "Development software (all)" << endl;
    PrintSofrware(root->children[3], false, false);

    DestructTree(root);
    return 0;
}