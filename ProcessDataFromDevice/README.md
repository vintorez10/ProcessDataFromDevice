At the very beginning of the task, it was known that the correct data transmitted by the device has this format:
struct {
            uint16_t header; //Заголовок, всегда равен 9887 (п.осн. 10)
            uint32_t id;     //id измерения
            uint64_t time_create; //время измерения
            uint8_t status_hardware; //статусное слово состояния аппаратной части
            uint8_t status_in_out;
            uint8_t status_device;
            uint8_t reserved;
            float data[21]; //данные от датчиков
            uint16_t crc;   //CRC16
    } data_struct;
    
    A binary file was proposed as a serial port dump file "data_hex".
    
    Having this file I need to:
    -Read data from a file (select using the file open dialog);
    -Define the beginning of the data;
    -Determine the presence and number of" broken " packets;
    -For each of the undamaged packets output data containing: "id", "time_create" and the first 17 sensors in qtableview;
    
    The size of the packages was determined by aligning the fields of the "data_struct" structure 
    and the preprocessor Directive "#Pragma pack" (https://habr.com/ru/post/142662/);
    
    We will display table data using the model/view architecture, the QTableView and QAbstractTableModel classes
    will be used for this purpose;
