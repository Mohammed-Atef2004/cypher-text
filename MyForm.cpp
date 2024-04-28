#include "MyForm.h"
#include <string>
#include <msclr/marshal_cppstd.h>
#include <iostream>

using namespace System;
using namespace System::Windows::Forms;

public ref class MyForm : public Form {
public:
    MyForm() {
        InitializeComponent();
    }

protected:
    ~MyForm() {
        {
        }
    }

private:
    TextBox^ inputTextBox;
    Button^ encryptButton;
    Button^ decryptButton;
    Label^ encryptedLabel;
    Label^ decryptedLabel;
    Label^ welcomeLabel;

    void InitializeComponent() {
        inputTextBox = gcnew TextBox();
        encryptButton = gcnew Button();
        decryptButton = gcnew Button();
        encryptedLabel = gcnew Label();
        decryptedLabel = gcnew Label();
        welcomeLabel = gcnew Label();
        // Other controls initialization code...

   
        


        // Form settings
        this->Text = "Caesar Cipher";
        this->WindowState = FormWindowState::Maximized; // Set window state to maximize
        this->StartPosition = FormStartPosition::CenterScreen;

        // Welcome Label
        welcomeLabel->Text = "enter the text and choose either encrypt or decrypt";
        welcomeLabel->Location = System::Drawing::Point::Point(50, 20);
        welcomeLabel->Size = System::Drawing::Size(800, 20);
        welcomeLabel->Font = gcnew System::Drawing::Font("Arial", 14);
        welcomeLabel->ForeColor = System::Drawing::Color::Black;
        this->Controls->Add(welcomeLabel);

        // TextBox
        inputTextBox->Location = System::Drawing::Point::Point(50, 60);
        inputTextBox->Size = System::Drawing::Size(500, 300);
        inputTextBox->Multiline = true; // Allow multiline input
        inputTextBox->ScrollBars = ScrollBars::Both; // Enable scrollbars
        this->Controls->Add(inputTextBox);

        // Encrypt Button
        encryptButton->Location = System::Drawing::Point::Point(50, 370);
        encryptButton->Size = System::Drawing::Size(80, 30);
        encryptButton->Text = "Encrypt";
        encryptButton->Click += gcnew EventHandler(this, &MyForm::Encrypt);
        this->Controls->Add(encryptButton);

        // Decrypt Button
        decryptButton->Location = System::Drawing::Point::Point(150, 370);
        decryptButton->Size = System::Drawing::Size(80, 30);
        decryptButton->Text = "Decrypt";
        decryptButton->Click += gcnew EventHandler(this, &MyForm::Decrypt);
        this->Controls->Add(decryptButton);

        // Encrypted Label
        encryptedLabel->Location = System::Drawing::Point::Point(50, 420);
        encryptedLabel->Size = System::Drawing::Size(500, 100);
       
        this->Controls->Add(encryptedLabel);
        encryptedLabel->Font = gcnew System::Drawing::Font("Arial", 9);
        encryptedLabel->ForeColor = System::Drawing::Color::Brown;
        // Decrypted Label
        decryptedLabel->Location = System::Drawing::Point::Point(50, 530);
        decryptedLabel->Size = System::Drawing::Size(500, 100);
        decryptedLabel->Font = gcnew System::Drawing::Font("Arial", 9);
        decryptedLabel->ForeColor = System::Drawing::Color::Blue;
        this->Controls->Add(decryptedLabel);
    }

    void Encrypt(Object^ sender, EventArgs^ e) {
        // Get input text from the TextBox
        String^ inputText = inputTextBox->Text;

        // Convert System::String^ to std::string
        std::string inputStr = msclr::interop::marshal_as<std::string>(inputText);

        // Perform encryption (Caesar cipher with shift of 3)
        std::string encryptedStr = caesarCipherEncrypt(inputStr, 3);

        // Convert std::string to System::String^
        String^ encryptedText = gcnew String(encryptedStr.c_str());

        // Display the encrypted text
        encryptedLabel->Text = encryptedText;
    }

    void Decrypt(Object^ sender, EventArgs^ e) {
        // Get input text from the TextBox
        String^ inputText = inputTextBox->Text;

        // Convert System::String^ to std::string
        std::string inputStr = msclr::interop::marshal_as<std::string>(inputText);

        // Perform decryption (Caesar cipher with shift of -3)
        std::string decryptedStr = caesarCipherDecrypt(inputStr, 3);

        // Convert std::string to System::String^
        String^ decryptedText = gcnew String(decryptedStr.c_str());

        // Display the decrypted text
        decryptedLabel->Text = decryptedText;
    }

    // Caesar cipher encryption function
    std::string caesarCipherEncrypt(const std::string& input, int shift) {
        std::string result = input;
        for (char& c : result) {
            if (isalpha(c)) {
                c = (c - 'a' + shift) % 26 + 'a'; // Encrypt lowercase letters
            }
            else if (isupper(c)) {
                c = (c - 'A' + shift) % 26 + 'A'; // Encrypt uppercase letters
            }
        }
        return result;
    }

    // Caesar cipher decryption function
    std::string caesarCipherDecrypt(const std::string& input, int shift) {
        return caesarCipherEncrypt(input, 26 - shift); // Reverse the shift to decrypt
    }
};

int main() {
    Application::Run(gcnew MyForm());
    return 0;
}
