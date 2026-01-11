#include<bits/stdc++.h>
using namespace std;

class TextView{
    public:
    virtual ~TextView() = default ;
    virtual void render() = 0;
};

class PlainText : public TextView {
    string text;
    public:
    PlainText(string text) : text(text){}

    void render() override {
        cout<<text;
    }
};

class TextDecorator : public TextView{
    protected :
    TextView *innerText;
    public :
    TextDecorator(TextView * inner) : innerText(inner){}
};

class BoldDecorator : public TextDecorator{
    public:
    BoldDecorator(TextView * inner) : TextDecorator(inner){}
    void render() override {
        cout<<"<b>";
        innerText->render();
        cout<<"</b>";
    }
};

class ItalicDecorator : public TextDecorator{
    public:
    ItalicDecorator(TextView * inner) : TextDecorator(inner){}
    void render() override {
        cout<<"<i>";
        innerText->render();
        cout<<"</i>";
    }
};

class UnderlineDecorator : public TextDecorator{
    public:
    UnderlineDecorator(TextView * inner) : TextDecorator(inner){}
    void render() override {
        cout<<"<u>";
        innerText->render();
        cout<<"</u>";
    }
};


int main(){
    PlainText text("Hello, World!");

    cout << "Plain: ";
    text.render();
    cout << endl;

    cout << "Bold: ";
    BoldDecorator boldText(&text);
    boldText.render();
    cout << endl;

    cout << "Italic + Underline: ";
    ItalicDecorator italic(&text);
    UnderlineDecorator italicUnderline(&italic);
    italicUnderline.render();
    cout << endl;

    cout << "Bold + Italic + Underline: ";
    BoldDecorator bold(&text);
    ItalicDecorator italicBold(&bold);
    UnderlineDecorator allStyles(&italicBold);
    allStyles.render();
    cout << endl;
    
    return 0;
}