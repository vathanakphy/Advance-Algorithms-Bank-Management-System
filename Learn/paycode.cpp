//nice
#include<iostream>
#include"../utils/User.hpp"
#include"../utils/Bank.hpp"
#include "../utils/Admin.hpp"
#include<cstdlib>
#define USER_FILE "user.bin"
class QRCode{
   private:
      int code;
      float amountKHR;
      float amountUSD;
   public:
      QRCode(){
         code = 0;
         amountUSD = 0.0;
         amountKHR = 0.0;
      }
      void cratePaymentCode(){
         //code
         int op;
         int random =0;
         srand((unsigned) time(NULL));
         cout<<"Choose Currency "<<endl;
         cout<<"1 . KHR"<<endl;
         cout<<"2 . USD"<<endl;
         cout<<" Choose : ";cin>>op;
         switch(op){
            case 1:
               cout<<"Amount (KHR) : ";cin>>amountKHR;
               random = 1000 + rand()%1000;
               //check validation
               code = random; //check is have or not
            break;
            case 2:
               cout<<"Amount (USD) : ";cin>>amountUSD;
               random = 1000 + rand()%1000;
               //check validation
               code = random; //check is have or not
            break;
         }
      }
      void payMoney(){
         //code
         // implement next time
      }
      string getCodeData(){
         if(amountKHR!=0){
            return to_string(code)+ " - " +to_string(round(amountKHR))+" R";
         }else{
            return to_string(code)+ " - " +to_string(amountUSD)+" $";
         }
      }
      int getCode() const {
         return code;
      }
      void setCode(int c) {
         code = c;
      }
      float getAmountKHR() const {
         return amountKHR;
      }
      void setAmountKHR(float amount) {
         amountKHR = amount;
      }
      float getAmountUSD() const {
         return amountUSD;
      }
      void setAmountUSD(float amount) {
         amountUSD = amount;
      }
};
int main(){
   LinkList<QRCode> usrs;
   QRCode usr;
   usr.cratePaymentCode();
   usrs.push(usr);
   usr.cratePaymentCode();
   usrs.push(usr);
   cout<<usrs.getValue(1).getCodeData()<<endl;
   return 0;
}