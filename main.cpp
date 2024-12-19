#include "./utils/User.hpp"
#include "./utils/Bank.hpp"
// #include "./utils/ATM.hpp"
#include "./utils/Admin.hpp"
#include "./utils/fileHandling.hpp"
#include <unistd.h>
#include <string>
#include <cstdlib>
#define DATA_USER "./Data/users.dat"
#define DATA_ADMIN "./Data/admin.dat"
#define BANK_USER "./Data/bank.dat"

// char* comfirmPassword();
bool enterPassword(User user);
int displayOption(string *allOption, int size);
void header(const string header);
void clearScreen();
void puseScreen();
int main()
{
   int option;
   string mainOption[] = {"ATM", "User", "Administration"};
   string userLoginOption[] = {"Login", "Register"};
   string userInterface[] = {"Check Balance", "Transaction History", "Transfer Money", "Payment",
                             "Deposit with Interest", "Loan", "Update Information", "Check Information Detail", "Request to Admin"};
   string transferOption[] = {"Transfer to Own Account", "Transfer to Other Account"};
   string payment[] = {"Create A payment code ", "Pay money"};
   string adminInterface[] = {
       "Create User Account", "Deposit", "Withdraw",
       "Search User Information", "Approve Loan", "Check Request",
       "Update Bank Data", "Show Transaction History", "Block User",
       "Check ATM History", "Write Report", "Bank Information"};
   string createAccount[] = {"Create User Account", "Create Many Account"};
   Bank bank;
   ATM atm;
   Admin admin;
   ArrayList<User> users;
   User newUser;
   int currentIndexUser = -1;

   // Load data to use
   bank.setExchnageRate(4100.00);
   readFromBinary(DATA_USER, users);
   admin.readBin(DATA_ADMIN);
   // admin.payInterest(users);
   do
   {
      clearScreen();
   START:
      header("KON KHMER BANK");
      switch (displayOption(mainOption, 3))
      {
      case 1:
      //ATM
         clearScreen();
         char phone[12], password[16];
         cout << "Enter Information to Login" << endl;
         cout << "Phone number: ";
         cin >> phone;
         currentIndexUser = indexOfUser(phone, users);
         if (currentIndexUser != -1)
         {
            cin.ignore();
            if (enterPassword(users.getValue(currentIndexUser)))
            {
               cout << "Login success ..." << endl;
               // Display ATM Menu
               atm.displayMenu(users.getValue(currentIndexUser));
            }
            else
            {
               cout << "Login failed. Incorrect password." << endl;
            }
         }
         else
         {
            cout << "User not found!" << endl;
         }
         break;
      case 2:
      USER:
         clearScreen();
         header("USER INTERFACE");
         option = displayOption(userLoginOption, 2);
         switch (option)
         {
         case 1:
            char phone[12], password[16];
            clearScreen();
            // for(int i=0;i<users.getLength();i++){
            //    users.getValue(i).output();
            // }
            cout << " Enter Information to Login" << endl;
            cout << "Phone number : ";
            cin >> phone;
            currentIndexUser = indexOfUser(phone, users);
            if (currentIndexUser != -1)
            {
               cin.ignore();
               if (enterPassword(users.getValue(currentIndexUser)))
               {
                  cout << "Login success ..." << endl;
               // apply some animetion
               userInterface:
                  clearScreen();
                  header("USER ACCOUNT");
                  int op;
                  cout << "Welcome back " << users.getValue(currentIndexUser).getFirstName() << endl;
                  op = displayOption(userInterface, 9);
                  switch (op)
                  {
                  // Code
                  case 1:
                  {
                     // Code Show Money of user
                     clearScreen();
                     header("USER BALANCE");
                     users.getValue(currentIndexUser).showBalance();
                     cout << "Press anykey Exit ... " << endl;
                     puseScreen();
                     break;
                  }
                  case 2:
                     clearScreen();
                     header("TRANSACTION HISTORY");
                     // Code Transaction History
                     for (string i : users.getValue(currentIndexUser).getHistoryTransaction())
                     {
                        cout << i;
                     }
                     cout << "Press anykey Exit ... " << endl;
                     puseScreen();
                     break;
                  case 3:
                     // Code transfer money ACLIDA Concept
                     clearScreen();
                     header("TRANSFER MONEY");
                     switch (displayOption(transferOption, 2))
                     {
                     case 1:
                     {
                        clearScreen();
                        header("TRANSFER TO OWN ACCOUNT");
                        users.getValue(currentIndexUser).transferOwnAccount(bank.getExchnageRate());
                        // need to write
                     }
                     break;
                     case 2:
                     {
                        // destination User
                        clearScreen();
                        header("TRANSFER TO OTHER ACCOUNT");
                        char phone[12];
                        cout << "Phone Number : ";
                        cin >> phone;
                        User &destUser = users.getValue(indexOfUser(phone, users));
                        users.getValue(currentIndexUser).transferToOtherAccount(destUser, bank.getExchnageRate());
                        writeToBinary(DATA_USER, users);
                        break;
                     }
                     case 0:
                     {
                        goto userInterface;
                        break;
                     }
                     }
                     cout << "Press anykey Exit ... " << endl;
                     puseScreen();
                     break;
                  case 4:
                     // Code payment
                     clearScreen();
                     header("PAYMENT TRANSACTION");
                     switch (displayOption(payment, 2))
                     {
                     case 1:
                        users.getValue(currentIndexUser).addQR();
                        writeToBinary(DATA_USER, users);
                        break;
                     case 2:
                     {
                        users.getValue(currentIndexUser).payMoney(users, currentIndexUser);
                        writeToBinary(DATA_USER, users);
                        break;
                     }
                     case 0:
                     {
                        goto userInterface;
                        break;
                     }
                     }
                     cout << "Press anykey Exit ... " << endl;
                     puseScreen();
                     break;
                  case 5:
                     // Code Deposit with Interest
                     clearScreen();
                     header("DEPOSIT WITH INTEREST");
                     try
                     {
                        users.getValue(currentIndexUser).addDepositWithInterest(bank);
                        admin.addlistUserDeposit((string)users.getValue(currentIndexUser).getPhoneNumber());
                        writeToBinary(DATA_USER, users);
                        admin.writeToBinary(DATA_ADMIN);
                     }
                     catch (exception &e)
                     {
                        cerr << e.what();
                     }
                     cout << "Press anykey Exit ... " << endl;
                     puseScreen();
                     break;
                  case 6:
                     // Code Apply Loan
                     clearScreen();
                     header("APPLY FOR LOAN");
                     // check loan is exit or not
                     if (!users.getValue(currentIndexUser).isHaveLoan())
                     {
                        Loan loan;
                        loan.applyLoan(users.getValue(currentIndexUser));
                        admin.requestLoan(loan);
                        admin.writeToBinary(DATA_ADMIN);
                        // write admin
                     }
                     else
                     {
                        cout << "You Have Loan. Need pay back money to Loan again" << endl;
                     }
                     cout << "Press anykey Exit ... " << endl;
                     puseScreen();
                     break;
                  case 7:
                     clearScreen();
                     header("UPDATE USER INFORMATION ");
                     // Code Update Information
                     users.getValue(currentIndexUser).updateUserInfo();
                     writeToBinary(DATA_USER, users);
                     break;
                  case 8:
                     // Code Check Information Detail
                     clearScreen();
                     users.getValue(currentIndexUser).displayInfo();
                     cin.ignore();
                     cout << "Press anykey Exit ... " << endl;
                     puseScreen();
                     break;
                  case 9:
                  {
                     // Code Request to Admin
                     string request;
                     Date date;
                     cin.ignore();
                     header("SENT REQUEST ");
                     cout << "Enter Request : ";
                     getline(cin, request);
                     date.setCurrentDate();
                     request = request + "\n\n" + date.getDate();
                     admin.addRequest(users.getValue(currentIndexUser), request);
                     admin.showRequest();
                     // ned to sacve to admin
                     cout << "Press anykey Exit ... " << endl;
                     puseScreen();
                     break;
                  }
                  case 0:
                  {
                     goto USER;
                     break;
                  }
                  }
                  puseScreen();
                  goto userInterface;
               }
            }
            else
            {
               currentIndexUser = -1;
               cout << "User Not Found" << endl;
               sleep(1);
               goto USER;
            }
            break;
         case 2:
         {
            clearScreen();
            header("Create User Account");
            newUser.input(DATA_USER);
            newUser.setTotalMoneyKHR(100000);
            newUser.setTotalMoneyUSD(100);
            if (users.getLength() > 0)
            {
               try
               {
                  if (newUser.findFreeOrder(users, newUser) == users.getLength())
                  {
                     users.push(newUser);
                  }
                  else
                  {
                     users.insertAt(newUser.findFreeOrder(users, newUser), newUser);
                  }
               }
               catch (exception &e)
               {
                  cerr << e.what();
               }
            }
            else
            {
               users.push(newUser);
            }
            writeToBinary(DATA_USER, users);
            cout << "Success" << endl;
            cout << "Press anykey Exit ... " << endl;
            puseScreen();
            break;
         }
         case 0:
            // exit
            goto START;
            break;
         }
         break;
      case 3:
         clearScreen();
         header("KON KHMER Administration");
      ADMIN_INTER:
         switch (displayOption(adminInterface, 12))
         {
         case 1:
            clearScreen();
            header("Create User Account");
            switch (displayOption(createAccount, 2))
            {
            case 1:
            {
               header("Create Account");
               User newUser;
               newUser.input(DATA_USER);
               if (users.getLength() > 0)
               {
                  try
                  {
                     if (newUser.findFreeOrder(users, newUser) == users.getLength())
                     {
                        users.push(newUser);
                     }
                     else
                     {
                        users.insertAt(newUser.findFreeOrder(users, newUser), newUser);
                     }
                  }
                  catch (exception &e)
                  {
                     cerr << e.what();
                  }
               }
               else
               {
                  users.push(newUser);
               }
               writeToBinary(DATA_USER, users);
               cout << "Success" << endl;
               cout << "Press anykey Exit ... " << endl;
               puseScreen();
               break;
            }
            case 2:
            {
               header("Create Many Account");
               string fileName;
               cout << "Enter File CSV : ";
               cin >> fileName;
               readFromCV(fileName, users, DATA_USER);
               cout << "Press anykey Exit ... " << endl;
               puseScreen();
               break;
            }
            case 0:
            {
               goto ADMIN_INTER;
               break;
            }
            }
            break;
         case 2:
         {
            clearScreen();
            char phone[12];
            QRCode deposit;
            header("Deposit");
            cout << "Phone Number : ";
            cin >> phone;
            int indexUser;
            try
            {
               indexUser = indexOfUser(phone, users);
               // use input password
            }
            catch (exception &e)
            {
               cerr << e.what();
            }
            if (indexUser != -1)
            {
               deposit.cratePaymentCode();
               if (deposit.getAmountKHR() > 0)
               {
                  admin.deposit(users.getValue(indexUser), deposit.getAmountKHR(), "KHR");
                  users.getValue(indexUser).logTransactionReceiveFromBank(deposit.getAmountKHR(), false);
               }
               else
               {
                  admin.deposit(users.getValue(indexUser), deposit.getAmountUSD(), "USD");
                  users.getValue(indexUser).logTransactionReceiveFromBank(deposit.getAmountUSD(), true);
               }
            }
            writeToBinary(DATA_USER, users);
            puseScreen();
            break;
         }
         case 3:
         {
            clearScreen();
            header("Withdraw");
            char phone[12];
            QRCode withdraw;
            header("Deposit");
            cout << "Phone Number : ";
            cin >> phone;
            int indexUser;
            try
            {
               indexUser = indexOfUser(phone, users);
            }
            catch (exception &e)
            {
               cerr << e.what();
            }
            if (indexUser != -1)
            {
               withdraw.cratePaymentCode();
               if (withdraw.getAmountKHR() > 0)
               {
                  admin.withdraw(users.getValue(indexUser), withdraw.getAmountKHR(), "KHR");
                  users.getValue(indexUser).logTransactionWithdraw(withdraw.getAmountKHR(), false);
               }
               else
               {
                  admin.withdraw(users.getValue(indexUser), withdraw.getAmountUSD(), "USD");
                  users.getValue(indexUser).logTransactionWithdraw(withdraw.getAmountUSD(), true);
               }
            }
            writeToBinary(DATA_USER, users);
            puseScreen();
            break;
         }
         case 4:
         {
            clearScreen();
            char phone[12];
            header("Search User Information");
            cout << "Phone number :";
            cin >> phone;
            try
            {
               admin.searchUserInformation(phone, users);
            }
            catch (exception &e)
            {
               cerr << e.what();
            }
            puseScreen();
            break;
         }
         case 5:
            clearScreen();
            header("Approve Loan");
            puseScreen();
            break;
         case 6:
            clearScreen();
            header("Check Request");
            admin.readBin(DATA_ADMIN);
            admin.showRequest();
            puseScreen();
            break;
         case 7:
            clearScreen();
            header("Update Bank Data");
            puseScreen();
            break;
         case 8:
            clearScreen();
            header("Show Transaction History");
            puseScreen();
            break;
         case 9:
            clearScreen();
            header("Block User");
            puseScreen();
            break;
         case 10:
            clearScreen();
            header("Check ATM History");
            puseScreen();
            break;
         case 11:
            clearScreen();
            header("Write Report");
            puseScreen();
            break;
         case 12:
         {
            clearScreen();
            header("Bank Information");
            puseScreen();
            break;
         }
         case 0:
         {
            goto START;
            break;
         }
         }
         puseScreen();
         goto ADMIN_INTER;
         break;
      case 0:
         clearScreen();
         cout << "Thank You" << endl;
         break;
      default:
         cout << "Invalid Input " << endl;
         break;
      }
      cin.ignore();
   } while (option != 0);

   return 0;
}

void clearScreen()
{
#ifdef _WIN32
   system("cls");
#else
   system("clear");
#endif
}
void puseScreen()
{
#ifdef _WIN32
   system("pause");
#else
   fflush(stdout); // Ensure the message is printed before waiting for input
   getchar();
#endif
}

void header(const string header)
{
   cout << "=========================================" << endl;
   cout << "         " << header << endl;
   cout << "=========================================" << endl
        << endl;
}
int displayOption(string *allOption, int size)
{
   string op;
   int choise;
   for (int i = 1; i <= size; i++)
   {
      cout << i << " . " << (allOption[i - 1]) << endl;
   }
   cout << "0 . Exit " << endl;
   cout << "Choose : ";
   cin >> op;
   try
   {
      choise = stoi(op);
      return choise;
   }
   catch (invalid_argument &e)
   {
      cerr << "Input Must be a number" << endl;
      sleep(1);
      return -1;
   }
}
// char comfirmPassword(char *cpassword) { // export from project term 2 year 1
//    char tempChar[50]="",tempCpass[50]="";
//    static char cpass[50];
//    int ascii,i=0;
//    while(1){
//       tempChar[i]=getch();
//       ascii=tempChar[i];
//       if(ascii==13){
//          break;
//       }else if((ascii==8) && (i>=0)){
//          printf("\b \b");
//          tempCpass[i]=tempCpass[i+1];
//          i--;
//       }else{
//          printf("*");
//          strcpy(tempCpass,tempChar);
//          i++;
//       }
//    }
// } implement next time
bool enterPassword(User user)
{
   int wrong = 0;
   char password[16];
enterPassword:
   cout << "Enter Passsword : ";
   cin >> password;
   if (strcmp(password, user.getPassword()) == 0)
   {
      cout << "Login Success . . ." << endl;
      return true;
   }
   else
   {
      wrong += 1;
      cout << "Incorect Password" << endl;
      sleep(1);
      if (wrong >= 3)
      {
         cout << "Incorect Password to many time" << endl;
         sleep(1);
         return false;
      }
      goto enterPassword;
   }
}