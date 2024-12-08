//nice
#include<iostream>
#include"../utils/User.hpp"
#include"../utils/Bank.hpp"
#define USER_FILE "user.dat"
int main(){
   ArrayList<User> user;
   int op;
   start:
      cout<<" 1 . Add User"<<endl;
      cout<<" 2 . Transfer"<<endl;
      cout<<"Choose : ";cin>>op;
      switch(op){
         case 1:{
            User tempUser;
            tempUser.input(USER_FILE);
            tempUser.setTotalMoneyUSD(100);
            tempUser.setTotalMoneyKHR(10000);
            tempUser.addQR();
            tempUser.showBalance();
            user.push(tempUser);
            tempUser.writeToFile(USER_FILE);
            break;
            }
         case 2:{  
            readFromBinary(USER_FILE,user);
            for(int i=0;i<user.getLength();i++){
               user.getValue(i).output();
               user.getValue(i).showBalance();
               for(auto i : user.getValue(i).getQR()){
                  cout<<i.getCodeData()<<" - "<<endl;
               }
            }
            char phone[12];
            int source,destination;
            source=1;
            user.getValue(source).payMoney(user,source);
            // cout<<"Phone Number : ";cin>>phone;
            // destination = bank.indexOfUser(phone,user);
            // // User& destinationUserñ = user.getValue(destination);
            // user.getValue(1).showBalance();
            // user.getValue(destination).showBalance();
            // if(destination!=-1){
            //    user.getValue(source).transferToOtherAccount(user.getValue(destination),4100.00);
            // }
            writeToBinary(USER_FILE,user);
            break;
            }
         // case 0:
         //    exit(2);
         // break;
      }
   goto start;
   cin.ignore();
   return 0;
}