// //nice
// #include<iostream>
// #include"../utils/User.hpp"
// // #include"../utils/Bank.hpp"
// #include "../utils/Admin.hpp"
// #include<cstdlib>
// #define USER_FILE "user.bin"
// class QRCode{
//    private:
//       int code;
//       float amountKHR;
//       float amountUSD;
//    public:
//       QRCode(){
//          code = 0;
//          amountUSD = 0.0;
//          amountKHR = 0.0;
//       }
//       void cratePaymentCode(){
//          //code
//          int op;
//          int random =0;
//          srand((unsigned) time(NULL));
//          cout<<"Choose Currency "<<endl;
//          cout<<"1 . KHR"<<endl;
//          cout<<"2 . USD"<<endl;
//          cout<<" Choose : ";cin>>op;
//          switch(op){
//             case 1:
//                cout<<"Amount (KHR) : ";cin>>amountKHR;
//                random = 1000 + rand()%1000;
//                //check validation
//                code = random; //check is have or not
//             break;
//             case 2:
//                cout<<"Amount (USD) : ";cin>>amountUSD;
//                random = 1000 + rand()%1000;
//                //check validation
//                code = random; //check is have or not
//             break;
//          }
//       }
//       string getCodeData(){
//          if(amountKHR!=0){
//             return to_string(code)+ " - " +to_string(round(amountKHR))+" R";
//          }else{
//             return to_string(code)+ " - " +to_string(amountUSD)+" $";
//          }
//       }
//       int getCode() const {
//          return code;
//       }
//       void setCode(int cj) {
//          code = c;
//       }
//       float getAmountKHR() const {
//          return amountKHR;
//       }
//       void setAmountKHR(float amount) {
//          amountKHR = amount;
//       }
//       float getAmountUSD() const {
//          return amountUSD;
//       }
//       void setAmountUSD(float amount) {
//          amountUSD = amount;
//       }
// };
// int main(){
//    LinkList<QRCode> usrs;
//    QRCode usr;
//    usr.cratePaymentCode();
//    usrs.push(usr);
//    usr.cratePaymentCode();
//    usrs.push(usr);
//    cout<<usrs.getValue(1).getCodeData()<<endl;
//    return 0;
// }

//nice

#include<iostream>
#include"../utils/User.hpp"
#include"../utils/Admin.hpp"

#define USER_FILE "user1.dat"

int main(){
   ArrayList<User> user;
   User tempUser;
   Bank bank;
   int op;
   Admin admin;
   start:
      cout<<" 1 . Add User"<<endl;
      cout<<" 2 . show"<<endl;
      cout<<" 3 . Save"<<endl;
      cout<<"Choose : ";cin>>op;
      switch(op){
         case 1:{
            tempUser.input(USER_FILE);
            tempUser.setTotalMoneyUSD(100);
            tempUser.setTotalMoneyKHR(1000000);
            tempUser.addDepositWithInterest(bank);
            tempUser.output();
            tempUser.writeToFile(USER_FILE);
            admin.addlistUserDeposit((string)tempUser.getPhoneNumber());
            user.push(tempUser);
            for(string i:admin.getlistUserDeposit()){
               cout<<i<<endl;
            }
            break;
         }
         case 2:{  
            readFromBinary(USER_FILE,user);
            for(int i=0;i<user.getLength();i++){
               Date cur;
               cur.nextManyMonth(1);
               user.getValue(i).payInterest(cur);

               for(auto j :user.getValue(i).getHistoryTransaction()){
                  cout<<j;
               }
               user.getValue(i).displayInfo();
            }
            break;
         }
         // case 3:
         // ofstream writeFile(USER_FILE,ios::binary);
         //    for(int i=0;i<user.getLength();i++){
         //       user.getValue(i).writeToFile(writeFile);
         //    }
         // break;
      }
   goto start;
   cin.ignore();
   return 0;
}