#include <bits/stdc++.h>

using namespace std;

class TextEditorMemento {
private:
   string state;

public:
   TextEditorMemento(string state) : state(state) {}

   string getState() {
       return state;
   }
};

class TextEditor {
private:
   string content;

public:
   TextEditor() : content("") {}

   void type(string newText) {
       content += newText;
       cout << "Typed: " << newText << endl;
   }

   string getContent() {
       return content;
   }

   TextEditorMemento save() {
       cout << "Saving state: \"" << content << "\"" << endl;
       return TextEditorMemento(content);
   }

   void restore(TextEditorMemento memento) {
       content = memento.getState();
       cout << "Restored state to: \"" << content << "\"" << endl;
   }
};

class TextEditorUndoManager {
private:
   stack<TextEditorMemento> history;

public:
   void save(TextEditor& editor) {
       history.push(editor.save());
   }

   void undo(TextEditor& editor) {
       if (!history.empty()) {
           editor.restore(history.top());
           history.pop();
       } else {
           cout << "Nothing to undo." << endl;
       }
   }
};

class TextEditorUndoV2 {
public:
   static void main() {
       TextEditor editor;
       TextEditorUndoManager undoManager;

       editor.type("Hello");
       undoManager.save(editor); // save state: Hello

       editor.type(" World");
       undoManager.save(editor); // save state: Hello World

       editor.type("!");
       cout << "Current Content: " << editor.getContent() << endl; // Hello World!

       cout << "\n--- Undo 1 ---" << endl;
       undoManager.undo(editor); // Back to: Hello World

       cout << "\n--- Undo 2 ---" << endl;
       undoManager.undo(editor); // Back to: Hello

       cout << "\n--- Undo 3 ---" << endl;
       undoManager.undo(editor); // Nothing left to undo
   }
};

int main() {
   TextEditorUndoV2::main();
   return 0;
}

