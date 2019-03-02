// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karolina on 16.01.2019.
//

#include "gtest/gtest.h"
#include "Report_Generation/Reporting.hpp"

/**
 * An assistant method. Compares content of two text files.
 * @param testing_ptr: one's file pointer
 * @param pattern_ptr: another's file pointer
 * @return true if files are the same
 */
bool compareFiles (FILE * testing_ptr, FILE * pattern_ptr) {
    char ch1 = getc(testing_ptr);
    char ch2 = getc(pattern_ptr);

    //error keeps track of number of errors
    //pos keeps track of position of errors
    //line keeps track of error line
    int error = 0, pos = 0, line = 1;

    //iterate loop till end of file
    while (ch1 != EOF && ch2 != EOF) {
        pos++;

        //if both variable encounters new line then
        //line variable is incremented
        //and pos variable is set to 0
        if (ch1 == '\n' && ch2 == '\n') {
            line++;
            pos = 0;
        }

        //if fetched data is not equal then
        //error is incremented
        if (ch1 != ch2) {
            error++;
            std::cout << "Line number: " << line << "Error position: " << pos << "\n";
        }

        //fetching character until end of file
        ch1 = getc(testing_ptr);
        ch2 = getc(pattern_ptr);
    }

    std::cout << "Total errors: " << error << "\n";
    fclose(testing_ptr);
    fclose(pattern_ptr);

    if (error != 0 ) {
        return false;
    }
    else {
        return true;
    }
}

/**
 * Test whether data is saved correctly (actual Factory class required).
 */
TEST(GenerateReportToFile, Structure) {
    Factory factory;
    ElementID ramp_id = 1;
    int ramp_delivery_interval = 3;
    ElementID worker_id = 1;
    int worker_process_interval = 2;
    QueueType worker_queue_type = QueueType::FIFO;
    ElementID storehouse_id = 1;

    factory.addRamp(ramp_id, ramp_delivery_interval);
    factory.addWorker(worker_id, worker_process_interval, worker_queue_type);
    factory.addStorehouse(storehouse_id);
    factory.addLink(ElementsOfNetwork::Ramp, ramp_id,ElementsOfNetwork::Worker, worker_id);
    factory.addLink(ElementsOfNetwork::Worker, worker_id,ElementsOfNetwork::Storehouse, storehouse_id);

    generateStructureReportToFile("TestEmpty.txt", factory);
    EXPECT_TRUE(generateStructureReportToFile("TestEmpty.txt", factory));

    FILE * testing_ptr;
    FILE * pattern_ptr;
    testing_ptr = fopen("TestEmpty.txt", "r");
    pattern_ptr = fopen("reportStructureTest.txt", "r");

    if (testing_ptr == nullptr) {
        std::cout << "Error while opening TestEmpty.txt during IOTest-Save implementing." << "\n";
    }

    pattern_ptr = fopen("saveTest.txt", "r");
    if (testing_ptr == nullptr) {
        std::cout << "Error while opening reportStructureTest.txt during IOTest-Save implementing." << "\n";
    }

    EXPECT_TRUE(compareFiles(testing_ptr, pattern_ptr));
}














// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)