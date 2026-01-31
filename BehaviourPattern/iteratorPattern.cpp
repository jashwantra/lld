#include <bits/stdc++.h>
using namespace std;

template<typename T>
class Iterator{
public:
    virtual ~Iterator() {}
    virtual bool hasNext() = 0;
    virtual T next() = 0;
};

template<typename T>
class IterableCollection{
public:
    virtual ~IterableCollection() {}
    virtual Iterator<T> * createIterator() = 0;
};

class Playlist;

class PlaylistIterator : public Iterator<string>{
private:
    Playlist* playlist;
    int index;
public:
    PlaylistIterator(Playlist * playlist_);
    bool hasNext() override ;
    string next() override;
};

class Playlist : public IterableCollection<string> {
private:
    vector<string> songs;
public:
    void addSong(string song){
        songs.push_back(song);
    }

    string getSongAt(int index){
        return songs[index];
    }

    int getSize() const{
        return songs.size();
    }

    Iterator<string> * createIterator(){
        return new PlaylistIterator(this);
    }
};

PlaylistIterator::PlaylistIterator(Playlist * playlist_):playlist(playlist_){}

bool PlaylistIterator::hasNext() {
    return index < playlist->getSize();
}

string PlaylistIterator::next() {
    return playlist->getSongAt(index++);
}

void musicPlayerDemo() {
    Playlist playlist;
    playlist.addSong("Shape of You");
    playlist.addSong("Bohemian Rhapsody");
    playlist.addSong("Blinding Lights");

    Iterator<string>* iterator = playlist.createIterator();

    cout << "Now Playing:" << endl;
    while (iterator->hasNext()) {
        cout << " 🎵 " << iterator->next() << endl;
    }

    delete iterator;
}

int main(){
    musicPlayerDemo();
    return 0;
}