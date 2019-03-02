// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)
//
// Created by Karolina on 09.01.2019.
//
#include "IO.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <cstdlib>
#include <string>
#include <vector>
#include <regex>
#include <map>
#include <iterator>
#include <stdexcept>



class UnknownElementException: public std::logic_error {
public:
    UnknownElementException(): std::logic_error("Unknown element of network occurred.") {}
};

class MissingInfoException: public std::logic_error {
public:
    MissingInfoException(): std::logic_error("There is not enough information about the element of the network.") {}
};

/**
 * Converts lines from the input into a vector structure.
 * @param lines_vector: vector of lines (type: string) from the input
 * @return vector of pairs marker-map[key-value]
 */
markers_t syntaxAnalysis(std::vector<std::string> lines_vector) {
    markers_t markers_with_data;

    std::string name1 = "LOADING_RAMP";
    std::string name2 = "WORKER";
    std::string name3 = "STOREHOUSE";
    std::string name4 = "LINK";

    for(auto &element: lines_vector) {
        std::size_t found1 = element.find(name1);
        std::size_t found2 = element.find(name2);
        std::size_t found3 = element.find(name3);
        std::size_t found4 = element.find(name4);

        if (found1!=std::string::npos || found2!=std::string::npos ||
        found3!=std::string::npos || found4!=std::string::npos) {
            std::vector<std::string> tokens;
            std::string token;

            std::istringstream token_stream(element);
            char delimiter = ' ';
            //podzielenie na 'klucz=wartość':
            while (std::getline(token_stream, token, delimiter)) {
                tokens.push_back(token);
            }

            std::string marker = tokens[0];
            tokens.erase(tokens.begin());

            std::map<std::string, std::string> marker_map;
            for (auto &pair: tokens) {
                std::vector<std::string> two_tokens;
                std::string small_token;

                std::istringstream small_token_stream(pair);
                char delimiter2 = '=';
                //podzielenie na 'klucz - wartość':
                while (std::getline(small_token_stream, small_token, delimiter2)) {
                    two_tokens.push_back(small_token);
                }

                marker_map.emplace(std::make_pair(small_token[0],small_token[1]));
                //marker_map.insert(std::make_pair(small_token[0],small_token[1]));
            }
            std::pair<std::string, std::map<std::string, std::string>> final_pair = std::make_pair(marker, marker_map);
            markers_with_data.push_back(final_pair);
        }

            //wyjątek
        else {
            throw UnknownElementException();  //rzucamy wyjątek
        }
    }
    return markers_with_data;
}

/**
 * Checks if elements of vector from synatxAnalysis():
 * contain all the information necessary to create a node of a given type
 * and whether they are given in the correct format and in the case of data correctness -
 * creating appropriate objects representing nodes within the Factory object.
 * @param initial_data: std::vector<std::pair<std::string, std::map<std::string, std::string>>> from synatxAnalysis() -
 * - vector of pairs marker-map[key-value]
 * @param factory: reference on structure's factory
 * @return nothing
 */
void semanticCorrectness(markers_t initial_data, Factory &factory) {
    for (auto const &pair: initial_data) {
        if (pair.first == "LOADING_RAMP") {
            if (pair.second.count("id") == 1) {
                if (pair.second.count("delivery-interval") == 1) {
                    std::string ramp_iden_str = pair.second.at("id");
                    std::stringstream ramp_iden_stream(ramp_iden_str);
                    ElementID ramp_iden_int;
                    ramp_iden_stream >> ramp_iden_int;

                    std::string delivery_str = pair.second.at("delivery-interval");
                    std::stringstream delivery_stream(delivery_str);
                    int delivery_int;
                    delivery_stream >> delivery_int;

                    factory.addRamp(ramp_iden_int, delivery_int);
                }
                else {
                    throw MissingInfoException();
                }
            } else {
                throw MissingInfoException();
            }
        }
        else if (pair.first == "WORKER") {
            if (pair.second.count("id") == 1) {
                if (pair.second.count("processing-time") == 1) {
                    if (pair.second.count("queue-type") == 1) {
                        std::string worker_iden_str = pair.second.at("id");
                        std::stringstream worker_iden_stream(worker_iden_str);
                        ElementID worker_iden_int;
                        worker_iden_stream >> worker_iden_int;

                        std::string processing_str = pair.second.at("processing-time");
                        std::stringstream processing_stream(processing_str);
                        int processing_int;
                        processing_stream >> processing_int;

                        std::string queue_str = pair.second.at("queue-type");
                        if (queue_str == "FIFO") {
                            QueueType queue_qt = QueueType::FIFO;
                            factory.addWorker(worker_iden_int, processing_int, queue_qt);
                        }
                        else if (queue_str == "LIFO") {
                            QueueType queue_qt = QueueType::LIFO;
                            factory.addWorker(worker_iden_int, processing_int, queue_qt);
                        }
                        else {
                            throw UnknownElementException();
                        }
                    }
                    else {
                        throw MissingInfoException();
                    }
                }
                else {
                    throw MissingInfoException();
                }
            } else {
                throw MissingInfoException();
            }
        }
        else if (pair.first == "STOREHOUSE") {
            if (pair.second.count("id") == 1) {
                std::string storehouse_iden_str = pair.second.at("id");
                std::stringstream storehouse_iden_stream(storehouse_iden_str);
                ElementID storehouse_iden_int;
                storehouse_iden_stream >> storehouse_iden_int;

                factory.addStorehouse(storehouse_iden_int);
            }
            else {
                throw MissingInfoException();
            }
        }
        else if (pair.first == "LINK") {
            if (pair.second.count("src") == 1) {
                if (pair.second.count("dest") == 1) {
                    //rozlozenie src na src_node_type i src_id_int
                    std::string src_str = pair.second.at("src");
                    std::vector<std::string> src_tokens;
                    std::string src_token;

                    std::istringstream src_token_stream(src_str);
                    char delimiter = '-';

                    while (std::getline(src_token_stream, src_token, delimiter)) {
                        src_tokens.push_back(src_token);
                    }

                    ElementsOfNetwork src_node_type;
                    if (src_tokens[0] == "ramp") {
                        src_node_type = ElementsOfNetwork::Ramp;
                    }
                    else if (src_tokens[0] == "worker") {
                        src_node_type = ElementsOfNetwork::Worker;
                    }
                    else {
                        throw UnknownElementException();
                    }
                    std::string src_id_str = src_tokens[1];
                    std::stringstream src_id_stream(src_id_str);
                    ElementID src_id_int;
                    src_id_stream >> src_id_int;

                    //rozlozenie dest na dest_node_type i dest_id_int
                    std::string dest_str = pair.second.at("dest");
                    std::vector<std::string> dest_tokens;
                    std::string dest_token;

                    std::istringstream dest_token_stream(dest_str);

                    while (std::getline(src_token_stream, src_token, delimiter)) {
                        dest_tokens.push_back(src_token);
                    }

                    ElementsOfNetwork dest_node_type;
                    if (dest_tokens[0] == "worker") {
                        dest_node_type = ElementsOfNetwork::Worker;
                    }
                    else if (dest_tokens[0] == "store") {
                        dest_node_type = ElementsOfNetwork::Storehouse;
                    }
                    else {
                        throw UnknownElementException();
                    }
                    std::string dest_id_str = dest_tokens[1];
                    std::stringstream dest_id_stream(dest_id_str);
                    ElementID dest_id_int;
                    dest_id_stream >> dest_id_int;

                    factory.addLink(src_node_type, src_id_int, dest_node_type, dest_id_int);
                }
                else {
                    throw MissingInfoException();
                }
            }
            else {
                throw MissingInfoException();
            }
        }

        else {
            throw MissingInfoException();
        }
    }
}

/**
 * Loads factory structure, using syntaxAnalysis() and semanticCorrectness().
 * @param input: std::ifstream from file or std::cin from console
 * @param factory: reference on structure's factory
 * @return true if there is no parsing errors
 */
bool loadFactoryStructure(std::istream &input, Factory &factory) {

    std::vector<std::string> lines;
    std::string one_line;
    std::regex pattern1("^\\s+");
    std::regex pattern2("^[;].+");

    //wektor linii bez ';' i niepustych
    if (input.good()) {
        while (!input.eof()) {
            std::getline(input, one_line);
            std::smatch result;
            if((std::regex_search(one_line, result, pattern1)) || (std::regex_search(one_line, result, pattern2))) {}
            else {
                lines.push_back(one_line);
            }
        }
    };

    try {
        syntaxAnalysis(lines);
    }
    catch (UnknownElementException &exception1) {
        std::cout << exception1.what() << std::endl;
        return false;
    }

    try {
        semanticCorrectness(syntaxAnalysis(lines), factory);
    }
    catch (UnknownElementException &exception2) {
        std::cout << exception2.what() << std::endl;
        return false;
    }
    catch (MissingInfoException &exception3) {
        std::cout << exception3.what() << std::endl;
        return false;
    }
    return true;
}


/**
 * Wraps the file from which we want to read the network structure with the requirements needed to
 * use loadFactoryStructure() and uses it.
 * @param filename: name of the file from which we want to read the network structure
 * @param factory: reference on structure's factory
 * @return true if there is no errors while loading the file
 */
bool loadFactoryStructureFromFile(std::string filename, Factory &factory) {
    std::ifstream file_str(filename, std::ios::in);

    if(file_str) {
        if(loadFactoryStructure(file_str, factory)) {
            file_str.close();
            return true;
        }
        else {
            std::cout << "ERROR: You can't load the file." << "\n";
            return false;
        }
    }
    else {
        std::cout << "ERROR: You can't open the file." << "\n";
        return false;
    }
}


/**
 * Saves the network structure into a file or into a console.
 * @param output: std::ofstream if file or std::cout if console
 * @param factory: reference on structure's factory
 * @return nothing
 */
void saveFactoryStructure(std::ostream &output, const Factory &factory) {
    const std::list<Ramp> &ramps_list = factory.getRamps().getNodes();
    const std::list<Worker> &workers_list = factory.getWorkers().getNodes();
    const std::list<Storehouse> &storehouses_list = factory.getStorehouses().getNodes();

    output << "; == LOADING RAMPS ==\n";
    output << " \n";
    for (const Ramp &ramp: ramps_list) {
        output << "LOADING_RAMP id=" << ramp.getID() << " delivery-interval=" << ramp.getDeliveryInterval() << "\n";
    }

    output << " \n";
    output << "; == WORKERS ==\n";
    output << " \n";
    for (const Worker &worker: workers_list) {
        QueueType queue_t = worker.getQueueType();
        std::string queue_t_str;
        if (queue_t == QueueType::FIFO) {
            queue_t_str = "FIFO";
        }
        else if (queue_t == QueueType::LIFO) {
            queue_t_str = "LIFO";
        }
        else {
            queue_t_str = "Invalid QueueType of the worker.";
        }
        output << "WORKER id=" << worker.getID() << " processing-time=" << worker.getProcessInterval() <<
        " queue-type=" << queue_t_str << "\n";
    }

    output << " \n";
    output << "; == STOREHOUSES ==\n";
    output << " \n";
    for (const Storehouse &storehouse: storehouses_list) {
        output << "STOREHOUSE id=" << storehouse.getID() << "\n";
    }

    output << " \n";
    output << "; == LINKS ==\n";
    output << " \n";
    for (const Ramp &ramp1: ramps_list) {
        //auto = std::map<std::shared_ptr<IPackageReceiver>, double>::const_iterator
        for(auto receiver_it = ramp1.getPreferences().begin();
        receiver_it != ramp1.getPreferences().end(); ++receiver_it) {
            ReceiverType dest_type = receiver_it->first->getReceiverType();
            std::string dest_type_str;
            if (dest_type == ReceiverType::Worker) {
                dest_type_str = "worker";
            }
            else if (dest_type == ReceiverType::Storehouse) {
                dest_type_str = "storehouse";
            }
            output << "LINK src=ramp-" << ramp1.getID() << " dest=" << dest_type_str << "-" <<
            receiver_it->first->getID() << "\n";
        }
        output << " \n";
    }

    for (const Worker &worker1: workers_list) {
        //auto = std::map<std::shared_ptr<IPackageReceiver>, double>::const_iterator
        for(auto receiver_it1 = worker1.getPreferences().begin();
        receiver_it1 != worker1.getPreferences().end(); ++receiver_it1) {
            ReceiverType dest_type = receiver_it1->first->getReceiverType();
            std::string dest_type_str;
            if (dest_type == ReceiverType::Worker) {
                dest_type_str = "worker";
            }
            else if (dest_type == ReceiverType::Storehouse) {
                dest_type_str = "store";
            }
            output << "LINK src=worker-" << worker1.getID() << " dest=" << dest_type_str << "-" <<
            receiver_it1->first->getID() << "\n";
        }
        output << " \n";
    }
}

/**
 * Wraps the file in which we want to save the network structure with the requirements needed to
 * use saveFactoryStructure() and uses it.
 * @param filename: name of the file in which we want to save the network structure
 * @param factory: reference on structure's factory
 * @return true if there is no errors while opening the file
 */
bool saveFactoryStructureToFile(std::string filename, const Factory &factory) {
    std::ofstream file_str(filename, std::ios::out | std::ios::trunc);

    if(file_str) {
        saveFactoryStructure(file_str, factory);
        file_str.close();
        return true;
    }
    else {
        std::cout << "ERROR: You can't open the file." << "\n";
        return false;
    }
}

// 4a_2: Stryczek (297457), Świerczek (297464), Śliwińska(297462)