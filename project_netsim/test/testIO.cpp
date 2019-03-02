// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karolina on 13.01.2019.
//

#include "gtest/gtest.h"
#include "IO.hpp"
#include <memory>
#include <fstream>
#include <stdio.h>

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
 * Test whether data is read correctly (actual Factory class required).
 */
TEST(IOTest, Load) {
    Factory factory;
    EXPECT_TRUE(loadFactoryStructureFromFile("struct-input.txt", factory));

    ElementID ramp_id = 1;
    int ramp_delivery_interval = 3;
    EXPECT_EQ(ramp_id, factory.findRampByID(ramp_id)->getID());
    EXPECT_EQ(ramp_delivery_interval, factory.findRampByID(ramp_id)->getDeliveryInterval());

    ElementID ramp_id1 = 2;
    int ramp_delivery_interval1 = 2;
    EXPECT_EQ(ramp_id1, factory.findRampByID(ramp_id1)->getID());
    EXPECT_EQ(ramp_delivery_interval1, factory.findRampByID(ramp_id1)->getDeliveryInterval());

    ElementID worker_id = 1;
    int worker_process_interval = 2;
    QueueType worker_queue_type = QueueType::FIFO;
    EXPECT_EQ(worker_id, factory.findWorkerByID(worker_id)->getID());
    EXPECT_EQ(worker_queue_type, factory.findWorkerByID(worker_id)->getQueueType());
    EXPECT_EQ(worker_process_interval, factory.findWorkerByID(worker_id)->getProcessInterval());

    ElementID worker_id1 = 2;
    int worker_process_interval1 = 1;
    QueueType worker_queue_type1 = QueueType::LIFO;
    EXPECT_EQ(worker_id1, factory.findWorkerByID(worker_id1)->getID());
    EXPECT_EQ(worker_queue_type1, factory.findWorkerByID(worker_id1)->getQueueType());
    EXPECT_EQ(worker_process_interval1, factory.findWorkerByID(worker_id1)->getProcessInterval());

    ElementID storehouse_id = 1;
    EXPECT_EQ(storehouse_id, factory.findStorehouseByID(storehouse_id)->getID());

    EXPECT_TRUE(factory.verifyCohesion());
    //EXPECT_EQ(worker_id, factory.findRampByID(ramp_id)->getPreferences()...->getID());

}


/**
 * Test whether data is saved correctly (actual Factory class required).
 */
TEST(IOTest, Save) {
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

    EXPECT_TRUE(saveFactoryStructureToFile("TestEmpty.txt", factory));

    FILE * testing_ptr;
    FILE * pattern_ptr;
    testing_ptr = fopen("TestEmpty.txt", "r");
    pattern_ptr = fopen("saveTest.txt", "r");

    if (testing_ptr == nullptr) {
        std::cout << "Error while opening TestEmpty.txt during IOTest-Save implementing." << "\n";
    }

    pattern_ptr = fopen("saveTest.txt", "r");
    if (testing_ptr == nullptr) {
        std::cout << "Error while opening saveTest.txt during IOTest-Save implementing." << "\n";
    }

    EXPECT_TRUE(compareFiles(testing_ptr, pattern_ptr));
}
// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)