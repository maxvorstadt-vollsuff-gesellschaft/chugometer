#include <Arduino.h>
#include <ArduinoJson.h>  // ArduinoJson library
#include <LittleFS.h> 

const char* file_paths[5] = {"/time_file_1.json", "/time_file_2.json", "/time_file_3.json", "/time_file_4.json", "/time_file_5.json"};
int file_pointer = 0;


void remove_json_file(int pointer) {
    const char* filePath = file_paths[pointer];
    Serial.println("In Remove function");
    if (!LittleFS.begin()) {
        Serial.println("Failed to mount file system");
        return;
    }
    if (LittleFS.exists(filePath)) {
        if (LittleFS.remove(filePath)) {
            Serial.println("File deleted successfully.");
        } else {
            Serial.println("Failed to delete the file.");
        }
    } else {
        Serial.println("File does not exist.");
    }
}

//noch nicht fertig
void remove_json_files() {
    //eigentlich i< file pointer
    for (int i = 0; i <= 4; ++i) {
        remove_json_file(i);
    }
}

void init_json_file(int pointer) {
    
    const char* filePath = file_paths[pointer];
    if (!LittleFS.begin()) {
        Serial.println("Failed to mount file system");
        return;
    }

    // Check if the file exists
    if (!LittleFS.exists(filePath)) {
        // Create and open the file
        File file = LittleFS.open(filePath, "w");
        if (!file) {
            Serial.println("Failed to create file");
            return;
        }

        // Create a JSON document and initialize it with an empty object
        StaticJsonDocument<2048> doc;
        doc.to<JsonObject>();  // Initialize as an empty object '{}'

        // Serialize the empty object to the file
        if (serializeJson(doc, file) == 0) {
            Serial.println("Failed to write to file");
        } else {
            Serial.println("JSON file initialized with an empty object");
        }

        // Close the file
        file.close();
    } else {
        Serial.println("JSON file already exists");
    }
}

//noch nicht fertig
void init_json_files() {
    file_pointer = 0;
    //eigentlich i< file pointer
    for (int i = 0; i <= 4; ++i) {
        init_json_file(i);
    }
}

void read_json_file(int pointer) {
    const char* filePath = file_paths[pointer];
// Initialize LittleFS
    Serial.println("Start Reading Process");
    if (!LittleFS.begin()) {
        Serial.println("Failed to mount file system");
        return;
    }

    // Open the file for reading
    File file = LittleFS.open(filePath, "r");

    // Check if the file opened successfully
    if (!file) {
        Serial.println("Failed to open file, but why");
        return;
    }

    StaticJsonDocument<2048> doc;

    // Deserialize the JSON document
    DeserializationError error = deserializeJson(doc, file);
    if (error) {
            Serial.print("Failed to read file, using default configuration: ");
            Serial.println(error.c_str());
            file.close();
            return;
        }
    serializeJsonPretty(doc, Serial);
}

boolean add_value_to_json(long id, int time) {

    if (file_pointer > 4)
    {
        return false;
    }

    const char* filePath = file_paths[file_pointer];
    File file = LittleFS.open(filePath, "r");
    StaticJsonDocument<2048> doc;

    if (file) {
        // Deserialize the JSON document from the file
        DeserializationError error = deserializeJson(doc, file);
        if (error) {
            Serial.print("Failed to read file, using default configuration: ");
            Serial.println(error.c_str());
            file.close();
            return false;
        }
        file.close();
    } else {
        // File does not exist, initialize with an empty object
        Serial.println("File does not exist. Return because I can not add  time anywhere.");
        return false;
    }

    if (doc["id"].add(id))
    {
        if (!doc["time"].add(time))
        {
            //delete ID item
            doc["id"].remove(doc["id"].size() - 1);
            ++file_pointer;
            return false;//Aufruf selbe function mit selben Werte oder return function mit bool
        }
        
    } else {
        return false;
        //Aufruf selbe function mit selben Werte oder return function mit bool
    }
    
    file = LittleFS.open(filePath, "w");
    if (!file) {
        Serial.println("Failed to open file for writing");
        return false;
    }

    if (serializeJson(doc, file) == 0) {
        Serial.println("Failed to write to file");
    } 

    // Close the file
    file.close();

    return true;
}

String get_json_string(int pointer) {
    String jsonString = "";
    File file = LittleFS.open(file_paths[pointer], "r");
    if (!file) {
        Serial.println("Failed to open file for reading");
        String message = "Failed reading";
        return message;
    }
    
    while (file.available()) {
        jsonString += char(file.read());
    }
    file.close();
    return jsonString;
}
