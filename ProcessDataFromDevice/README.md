    Hello everyone!))
    At the very beginning of the task, it was known that the correct data transmitted by the device has the format
    that is presented in this file: "data_struct.txt";     
    
    A binary file was proposed as a serial port dump file "data_hex".
    
    Having this file I need to:
    -Read data from a file (select using the file open dialog);
    -Define the beginning of the data;
    -Determine the presence and number of" broken " packets;
    -For each of the undamaged packets output data containing: "id", "time_create" and the first 17 sensors in qtableview;
    
    The size of the packages was determined by aligning the fields of the "data_struct" structure 
    and the preprocessor Directive "#Pragma pack" (https://habr.com/ru/post/142662/);
    
    We will display table data using the model / view architecture, 
    the QTableView and QAbstractTableModel classes were used for this purpose;
   
   Bye!))
