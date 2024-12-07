#ifndef CLASS_USER
#define CLASS_USER
#include<stack>
#include<cstring>
#include<cmath>
#include "./DOB.hpp"
#include "./fileHandling.hpp"
#include "./arrayList.hpp"
#include "QRCode.hpp"
class User{
private:
   string firstName;
   string lastName;
   DOB dob;
   long nationalIdCard;
   char phoneNumber[16];
   string address;
   double loanUSD;
   double loanKHR;
   double totalMoneyKHR;
   double totalMoneyUSD;
   char password[16];
   // ArrayList<QRCode> qrCode;
public:
   User(){
      firstName = "NULL";
      lastName = "NULL";
      address = "NULL";
      strcpy(phoneNumber, "NULL");
      strcpy(password, "NULL");
      nationalIdCard=0;
      loanKHR=0.00;
      loanUSD=0.00;
      totalMoneyKHR=0.00;
      totalMoneyUSD=0.00;
   }
   void input(const string &fileName){
      // string fname;
      cout<<"User information "<<endl;
      cout<<"First Name : ";cin>>firstName;
      // stringToChar (&firstName,fname);
      // cout<<"Last Name  : ";cin>>lastName;
      // cout<<"National ID Card : ";cin>>nationalIdCard;
      // cin.ignore();
      // cout<<"Address    : ";getline(cin,address);
      // dob.inputDate();
      // cin.ignore();
      cout<<"Security Section "<<endl;
      // inputPhoneNumber(fileName);
      inputPassword();
   }
   void writeToFile(const string &fileName){
      ofstream writeFile(fileName, ios::app | ios::binary);
      writeString(writeFile,firstName);
      writeString(writeFile,lastName);
      writeFile.write((char *)(&dob), sizeof(DOB));
      writeFile.write((char *)(&nationalIdCard), sizeof(nationalIdCard));
      writeFile.write((char *)(&phoneNumber), sizeof(phoneNumber));
      writeString(writeFile,address);
      writeFile.write((char *)(&loanUSD), sizeof(loanUSD));
      writeFile.write((char *)(&loanKHR), sizeof(loanKHR));
      writeFile.write((char *)(&totalMoneyKHR), sizeof(totalMoneyUSD));
      writeFile.write((char *)(&password), sizeof(password));
      // qrCode.writeArrayList(writeFile);
      writeFile.close();
   }
   void readFileBin(ifstream &readFile){
      firstName = readString(readFile);
      lastName = readString(readFile);
      readFile.read((char *)(&dob), sizeof(dob));
      readFile.read((char *)(&nationalIdCard), sizeof(nationalIdCard));
      readFile.read((char *)(&phoneNumber), sizeof(phoneNumber));
      address = readString(readFile);
      readFile.read((char *)(&loanUSD), sizeof(loanUSD));
      readFile.read((char *)(&loanKHR), sizeof(loanKHR));
      readFile.read((char *)(&totalMoneyKHR), sizeof(totalMoneyKHR));
      readFile.read((char *)(&password), sizeof(password));
      // qrCode.readArrayList(readFile);
   }
   void inputPhoneNumber(const string &fileName){
      enterPhonenumber:
      cout<<"Phone Number : ";cin>>phoneNumber;
      //add validation
      if(isPhoneNumberUsed(fileName,phoneNumber)){
         cout<<"Check"<<endl;
         cerr<<"Phone Number has been used "<<endl;
         cerr<<"Enter it again"<<endl;
         goto enterPhonenumber;
      }
   }
   bool isPhoneNumberUsed(const string fileName,const char *phoneNumber){
      //add code
      ArrayList<User> tempUser;
      readFromBinary(fileName,tempUser);
      char phone[16];
      for(int i=0;i<tempUser.getLength();i++){        
         strcpy(phone,tempUser.getValue(i).getPhoneNumber());
         if(strcmp(phoneNumber,phone)==0) return true;
      }
      return false;
   }
   void inputPassword(){
      char confirmPassword[16];
      char pass[16];
      enterPassword:
      cout<<"Password   : ";cin>>pass;
      cout<<"Confirm Password : ";cin>>confirmPassword;
      if(strcmp(confirmPassword,pass)!=0){
         cout<<"Confirm Password Incorrect "<<endl;
         cout<<"Enter password again"<<endl;
         goto enterPassword;
      }
      strcpy(password,pass);
   }
   void output(){
      cout<<firstName<<" "<<phoneNumber<<endl;
   }
   void showBalance(){
      cout << "Account Balance:" << endl;
      cout << " - KHR: " << totalMoneyKHR <<"R"<< endl;
      cout << " - USD: " << totalMoneyUSD <<"$"<< endl;
   }
   bool checkSourceUSD(double usd){
      if(usd<=totalMoneyUSD){
         if(usd <= 0){
            throw runtime_error("Invalid Input\n");
         }else{
            return true;
         }
      }else{
         throw runtime_error("Not Enough Money\n");
         return false;
      }
   }
   bool checkSourceKHR(double khr){
      if(khr<=totalMoneyKHR){
         if(khr <= 0){
            throw runtime_error("Invalid Input\n");
         }else{
            return true;
         }
      }else{
         throw runtime_error("Not Enough Money\n");
         return false;
      }
   }
   double changeUSDtoKHR(double usd,float exchangeRate){
      usd*=exchangeRate;
      return usd;
   }
   double changeKHRtoUSD(double khr,float exchangeRate){
      khr/=(double)exchangeRate;
      return round(khr*1000.0)/1000.0;
   } 
   void transferOwnAccount(float exchangeRate){
      int op;
      double usd;
      double khr;
      cout<<"1 . From USD to KHR "<<endl;
      cout<<"2 . From KHR to USD "<<endl;
      cout<<"0 . Exit"<<endl;
      cout<<"Choose :";cin>>op;
      switch(op){
         case 1:
            cout<<"Amount (USD) : ";cin>>usd;
            //check validation when transfer
            try{
               checkSourceUSD(usd);
               setTotalMoneyKHR(totalMoneyKHR+changeUSDtoKHR(usd,exchangeRate));
               setTotalMoneyUSD(totalMoneyUSD-usd);
               cout<<"Transfer Success"<<endl;
            }catch(exception &e){
               cerr<<e.what();
            };
            break;
         case 2:
            cout<<"Amount (KHR) : ";cin>>khr;
            //check validation when transfer
            try{
               checkSourceKHR(khr);
               setTotalMoneyKHR(totalMoneyKHR-khr);
               setTotalMoneyUSD(totalMoneyUSD+changeKHRtoUSD(khr,exchangeRate));
               cout<<"Transfer Success"<<endl;
            }catch(exception &e){
               cerr<<e.what();
            };
            break;
         case 0:
            exit(2);
            break;
      }
   }
   bool isUSDAccount(){
      int op;
      cout<<"Choose Account : "<<endl;
      cout<<"1 . USD "<<phoneNumber<<endl;
      cout<<"2 . KHR "<<phoneNumber<<endl;
      // cout<<"0 . Exit"<<endl; we will improve this function to exit 
      cout<<"Choose :";cin>>op;
      if(op == 1) return true;
      return false;
   }
   void transferToOtherAccount(User &destUser,float exchangeRate){
      double usd,khr;
      int op;
      cout<<"Choose Currency"<<endl;
      cout<<"Destination : "<<destUser.getPhoneNumber()<<destUser.getFirstName()<<endl;;
      cout<<"1 . USD "<<endl;
      cout<<"2 . KHR "<<endl;
      cout<<"0 . Exit"<<endl;
      cout<<"Choose : ";cin>>op;
      switch(op){
         case 1:
            cout<<"Amount (USD) : ";cin>>usd;
            //check validation when transfer
            try{
               if(isUSDAccount()){
                  checkSourceUSD(usd);
                  setTotalMoneyUSD(totalMoneyUSD-usd);
                  destUser.setTotalMoneyUSD(destUser.getTotalMoneyUSD()+usd);
                  cout<<"Transfer Success"<<endl;
               }else{
                  checkSourceKHR(changeUSDtoKHR(usd,exchangeRate));
                  setTotalMoneyKHR(totalMoneyKHR-changeUSDtoKHR(usd,exchangeRate));
                  destUser.setTotalMoneyUSD(destUser.getTotalMoneyUSD()+usd);
                  cout<<"Transfer Success"<<endl;
               }
            }catch(exception &e){
               cerr<<e.what();
            };
            break;
         case 2:
            cout<<"Amount (KHR) : ";cin>>khr;
            //check validation when transfer
            try{
               if(!isUSDAccount()){
                  checkSourceKHR(khr);
                  setTotalMoneyKHR(totalMoneyKHR-khr);
                  destUser.setTotalMoneyKHR(destUser.getTotalMoneyKHR()+khr);
                  cout<<"Transfer Success"<<endl;
               }else{
                  checkSourceUSD(changeKHRtoUSD(khr,exchangeRate));
                  setTotalMoneyUSD(totalMoneyUSD-changeKHRtoUSD(khr,exchangeRate));
                  destUser.setTotalMoneyKHR(destUser.getTotalMoneyKHR()+khr);
                  cout<<"Transfer Success"<<endl;
               }   
            }catch(exception &e){
               cerr<<e.what();
            };
            break;
         case 0:
            exit(2);
            break;
      }
   }
   // void addQR(){
   //    QRCode newQR;
   //    newQR.cratePaymentCode();
   //    cout<<newQR.getCodeData()<<endl;
   //    qrCode.push(newQR);
   // }
   // bool checkQRCode(const int code,int &index){
   //    for(int i=0;i<qrCode.getLength();i++){
   //       if(qrCode.getValue(i).getCode() != code) {
   //          index = i;
   //          return false;     
   //       }
   //    }
   //    return true;
   // }
   // void payMoney(ArrayList<User> &destUsers,int indexSource){
   //    //code
   //    int tempCode=0;
   //    int indexQRCode=0;
   //    string confirm;
   //    cout<<"Enter Code : ";cin>>tempCode;
   //    for(int i = 0; i<destUsers.getLength();i++){
   //       if(i == indexSource) continue;
   //       if(checkQRCode(tempCode,indexQRCode)){
   //          cout<<destUsers.getValue(i).getFirstName()<<endl;
   //          cout<<destUsers.getValue(i).getPhoneNumber()<<endl;
   //          QRCode& codeToPay = destUsers.getValue(i).getQR().getValue(i);
   //          cout<<codeToPay.getCodeData()<<endl;
   //          // cout<<"press Yes/No to pay";cin>>confirm;
   //          // if(confirm == "yes" ){
   //             cout<<"Process Pay..";
   //          // }
   //       }else{
   //          cout<<"Code not found"<<endl;
   //       }
   //    }
   // }
   char* getPhoneNumber() { 
   return phoneNumber; 
   }

   void setPhoneNumber(const char* number) { 
      strncpy(phoneNumber, number, sizeof(phoneNumber) - 1); 
      phoneNumber[sizeof(phoneNumber) - 1] = '\0'; 
   }

   string getFirstName() { 
      return firstName; 
   }

   void setFirstName(const string firstName) { 
      this->firstName = firstName;
   }

   string getLastName() { 
      return lastName; 
   }

   void setLastName(const string lastName) { 
      this->lastName = lastName;
   }

   string getAddress() { 
      return address; 
   }

   void setAddress(const string address) { 
      this->address = address;
   }

   long getNationalIdCard() { 
      return nationalIdCard; 
   }

   void setNationalIdCard(long id) { 
      nationalIdCard = id; 
   }
   string getUserDOB(){
      return dob.getDOB();
   }
   double getLoanUSD() { 
      return loanUSD; 
   }

   void setLoanUSD(double loan) { 
      loanUSD = loan; 
   }

   double getLoanKHR() { 
      return loanKHR; 
   }

   void setLoanKHR(double loan) { 
      loanKHR = loan; 
   }

   double getTotalMoneyKHR() { 
      return totalMoneyKHR; 
   }

   void setTotalMoneyKHR(double total) { 
      totalMoneyKHR = total; 
   }

   double getTotalMoneyUSD() { 
      return totalMoneyUSD; 
   }

   void setTotalMoneyUSD(double total) { 
      totalMoneyUSD = total; 
   }

   char* getPassword() { 
      return password; 
   }

   void setPassword(const char* pwd) { 
      strncpy(password, pwd, sizeof(password) - 1); 
      password[sizeof(password) - 1] = '\0'; 
   }
   // ArrayList<QRCode> &getQR(){
   //    return qrCode;
   // }

   // int getQrCodePayment() { 
   //    return qrCodePayment; 
   // }

   // void setQrCodePayment(int code) { 
   //    qrCodePayment = code; 
   // }      
};
#endif