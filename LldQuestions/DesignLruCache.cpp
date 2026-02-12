#include <bits/stdc++.h>
using namespace std;

template <typename K, typename V>
struct Node{
    Node * prev;
    Node * next;
    K key;
    V value;
    Node(K key_, V value_):key(key_), value(value_), prev(nullptr), next(nullptr){}
};

template<typename K, typename V>
class DoublyLinkedList{
private:
    Node<K,V> *head;
    Node<K,V> *tail;
public:
    DoublyLinkedList(){
        head = new Node<K,V>(K(), V());
        tail = new Node<K,V>(K(), V());
        head->next=tail;
        head->prev=tail;
        tail->next=head;
        tail->prev=head;
    }

    ~DoublyLinkedList(){
        delete head;
        delete tail;
    }

    void addFirst(Node<K,V> *node){
        node->prev=head;
        node->next=head->next;
        head->next=node;
        node->next->prev=node;
    }

    Node<K,V> * insert(K key, V value){
        Node<K,V> *newNode = new Node<K,V>(key, value);
        addFirst(newNode);
        return newNode;
    }

    void remove(Node<K,V> * node){
        node->prev->next = node->next;
        node->next->prev = node->prev;
        delete node;
    }

    void moveToFront(Node<K,V> *node){
        node->prev->next = node->next;
        node->next->prev = node->prev;
        addFirst(node);
    }

    K removeLast(){
        if(tail->prev == head)
            return K();
        Node<K,V> *node=tail->prev;
        K key = node->key;
        remove(node);
        return key;
    }
};

template<typename K, typename V>
class LruCache{
private:
    int capacity;
    DoublyLinkedList<K,V> doublyLinkedList;
    map<K, Node<K,V> *> mp;
    mutable mutex mtx;
public:
    LruCache(int capacity_):capacity(capacity_){
        // cout<<"LruCache with capacity "<<capacity<<"\n";
    } 

    ~LruCache(){
        for(auto it:mp){
            delete it.second;
        }
    }

    V get(K key){
        lock_guard<mutex> lock(mtx);
        if(mp.find(key) == mp.end())
            return -1;
        doublyLinkedList.moveToFront(mp[key]);
        
        return mp[key]->value;
    }

    void put(K key, V value){
        lock_guard<mutex> lock(mtx);

        if(mp.find(key) == mp.end()){
            if(mp.size() == capacity){
                // mp.erase(key);
                mp.erase(doublyLinkedList.removeLast());
            }
            mp[key]=doublyLinkedList.insert(key,value);
        }
        else    
            doublyLinkedList.moveToFront(mp[key]);
    }  
};

class LRUCacheDemo {
public:
    static void main() {
        LruCache<string, int>* cache = new LruCache<string, int>(3);

        cache->put("a", 1);
        cache->put("b", 2);
        cache->put("c", 3);

        cout << cache->get("a") << endl; // 1

        cache->put("d", 4);
        
        cout << cache->get("b") << endl; // 0 (null equivalent)
    }
};

int main(){
    LRUCacheDemo::main();
    return 0;
}