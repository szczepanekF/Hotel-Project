# **Hotel-Project**
A desktop application which allows user to create reservations, look through old and upcoming reservations, manage them, and manage his account. 
## Requirements
- c++ wxWidgets 3.0
- c++ BOOST library
### How to run it
You have to change server/server.py CPPcon class attribute named 'server', and project/library/src/socket/C_client.cpp define value also named 'server' to your local ip address. <br />
Then you run the python script, which is contained in 'server' directory, to make connection with database possible, and later you run the c++ project ('program' subproject), which happens to be in 'project' directory (preferably on linux as wxWidgets works differently on different operating systems this app was written and tested on linux) and evertyhing should be working flawlessly :).

## ScreenShots


![Logging Panel](https://user-images.githubusercontent.com/107700989/226107813-239dbdba-9b44-4e03-8c65-3da465cb123d.png)
![Register Panel](https://user-images.githubusercontent.com/107700989/226107869-6217fe38-5053-4ce0-8f67-1244a93a5e9d.png)
![Menu Panel](https://user-images.githubusercontent.com/107700989/226107883-d45a0357-c623-4ed3-b098-0d1953640e25.png)
![Reservations Panel](https://user-images.githubusercontent.com/107700989/226107897-72060c7d-c9b1-40d7-a436-ba2ad62e466b.png)
![Reservations Panel Change Option ](https://user-images.githubusercontent.com/107700989/226107913-53fcf4c2-1a56-4dec-879c-284f6ed38cde.png)
![Reservations Panel Cancell Option](https://user-images.githubusercontent.com/107700989/226107918-b295d72a-b390-4e30-8029-32152f3f25a7.png)
![Rooms Panel](https://user-images.githubusercontent.com/107700989/226107951-8a15bf5a-f5cf-431c-b3a8-f0dd4bd9044f.png)
![Settings Panel](https://user-images.githubusercontent.com/107700989/226107947-0f5b6c91-4b48-46cb-ba8a-8692ce5bf239.png)
