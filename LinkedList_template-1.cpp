#include<iostream>
#include<memory>
#include<vector>
#include<string>


template<typename T> 
class Node {

public:
 std::string url; 
 std::string name; 
 T memory; 

std::shared_ptr<Node<T>> next;
std::shared_ptr<Node<T>> prev;

 public:
 Node(std::string url, std::string name, T memory){
this->url = url;    
this->name = name;
this->memory = memory;
next = nullptr; 
prev = nullptr; 

 }
 std::string getUrl() {

    return this->url;
 }
std::string getName() {
    return this->name;
}


};

template<typename T>
class Browser {

public:

 std::shared_ptr<Node<T>> head; 
 std::shared_ptr<Node<T>> tail;
 std::shared_ptr<Node<T>> currentTab;
 std::vector<std::pair<std::string, std::string>> bookmarks;

 int size; 


Browser() {
head = nullptr; 
tail = nullptr; 
size = 0;  

}



void addNewTab(std::string url, std::string name, T memory ){

    std::shared_ptr<Node<T>> newBrowser = std::make_shared<Node<T>>(url, name, memory); 

    if (head == nullptr)
    {
        head = newBrowser;
        tail = newBrowser; 
        currentTab = newBrowser;
    }
    else {
     tail->next = newBrowser;
     newBrowser->prev = tail;
     tail = newBrowser; 
     currentTab = tail;
   

    }


size++; 

}


void switchToPrevTab()  {


if (currentTab->prev == nullptr)
{
    std::cout << "No previous tab" <<std::endl;
}
else {

currentTab = currentTab->prev;

std::cout <<"url " << currentTab->url << "name " << currentTab->name << " memory " << currentTab->memory << std::endl; 

}


}

void switchToNextTab() {

if (currentTab->next != nullptr)
{
    currentTab = currentTab->next;
    std::cout <<"url " << currentTab->url << "name " << currentTab->name << " memory " << currentTab->memory << std::endl; 

}
else {


    std::cout << "No next tab" <<std::endl;
}


}


void closeCurrentTab() {

if (currentTab == head) {

    head = currentTab->next; 
    head->prev = nullptr;
    currentTab = head;
}
else if (currentTab == tail)
{
    tail = currentTab->prev;
    tail->next = nullptr;
    currentTab = tail;

}
else {

currentTab->prev->next = currentTab->next;
currentTab->next->prev = currentTab->prev;




}

size--;

}
void bookmarkCurrent() {
        if (!currentTab) {
            std::cout << "No current tab to bookmark" << std::endl;
            return;
        }

        for (const auto& bookmark : bookmarks) {
            if (bookmark.first == currentTab->getUrl() && bookmark.second == currentTab->getName()) {
                std::cout << "The bookmark is already added!!" << std::endl;
                return;
            }
        }

        bookmarks.push_back(std::make_pair(currentTab->getUrl(), currentTab->getName()));
        std::cout << "Bookmark added for " << currentTab->getName() << std::endl;
    }


    void showBookmarkTab() {
  if (bookmarks.empty()) {
        std::cout << "No bookmarks available" << std::endl;
        return;
    }

    std::cout << "Bookmarked Tabs:" << std::endl;
    for (const auto& bookmark : bookmarks) {
        std::cout << "URL: " << bookmark.first << ", Name: " << bookmark.second << std::endl;
    }

    
}

void  moveCurrentToFirst() {

   std::shared_ptr<Node<T>>  temp = currentTab; 
    closeCurrentTab(); 
    temp->next = head; 
    head->prev = temp; 
    temp->prev = nullptr;
    head = temp;


}








T total_memory() {
    T total = T(); 

    auto temp = head; 
    while (temp != nullptr) {
        total += temp->memory; 
        temp = temp->next;
    }

    return total; 
}



void deleteTab() {
    if (!head) {
        std::cout << "No tabs to delete" << std::endl;
        return;
    }

    std::shared_ptr<Node<T>> tabToDelete = head;
    std::shared_ptr<Node<T>> temp = head;

    while (temp != nullptr) {
        if (tabToDelete->memory < temp->memory) {
            tabToDelete = temp;
        }
        temp = temp->next;
    }

    if (tabToDelete == head) {
        head = tabToDelete->next;
        if (head)
            head->prev = nullptr;
    } else if (tabToDelete == tail) {
        tail = tabToDelete->prev;
        if (tail)
            tail->next = nullptr;
    } else {
        tabToDelete->prev->next = tabToDelete->next;
        tabToDelete->next->prev = tabToDelete->prev;
    }

    std::cout << "Deleted tab: " << tabToDelete->name << " Memory consumption: " << tabToDelete->memory << std::endl;
    size--;
}



 






void display(){
auto curr = head;
std::cout<<"Browser tab list = "<<std::endl;
while(curr){
std::cout<<"| "<<curr->name<<" x|-->";
curr = curr->next;
}
std::cout<<std::endl;
std::cout<<std::endl;
}




};


int main(){


Browser<double> b1;
b1.addNewTab("https://www.google.com","Google",23.45);
b1.display();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
std::cout<<"Switch to Next tab = "<<std::endl;
b1.switchToNextTab();
b1.addNewTab("https://www.youtube.com","YouTube",56);
b1.bookmarkCurrent();
b1.display();
b1.addNewTab("https://www.geeksforgeeks.com","GeeksForGeeks",45.78);
b1.bookmarkCurrent();
b1.addNewTab("https://chat.openai.com","ChatGPT",129);
b1.addNewTab("https://linkedin.com","LinkedIn",410);
b1.bookmarkCurrent();
b1.addNewTab("https://github.com","Github",110);
b1.addNewTab("https://kaggle.com","Kaggle",310);
b1.bookmarkCurrent();
b1.display();
std::cout<<"Total memory consumption = "<<b1.total_memory()<<"MB"<<std::endl;
b1.showBookmarkTab();
b1.moveCurrentToFirst();
b1.display();
b1.deleteTab();
b1.display();
std::cout<<"Switch to next tab = "<<std::endl;
b1.switchToNextTab();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
b1.closeCurrentTab();
b1.display();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
b1.closeCurrentTab();
b1.display();
b1.showBookmarkTab();
std::cout<<"Total Memory Consumption = "<<b1.total_memory()<<"MB"<<std::endl;
b1.deleteTab();
b1.display();
b1.addNewTab("https://docs.google.com/","Google Docs",102.34);
b1.display();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
std::cout<<"Switch to previous tab = "<<std::endl;
b1.switchToPrevTab();
b1.bookmarkCurrent();
b1.showBookmarkTab();
b1.total_memory();
b1.deleteTab();
b1.display();




return 0;
}
