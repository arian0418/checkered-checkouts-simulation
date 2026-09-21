#include <iomanip>
#include <iostream>
#include <limits>
#include <random>

class Customer {
private:
    int customerID;
    int items;
    double itemsCost;
    Customer* next;
    static int nextCustomerID;

public:
    Customer(int itemCount, double cost)
        : customerID(++nextCustomerID), items(itemCount),
          itemsCost(cost), next(nullptr) {}

    int getCustomerID() const { return customerID; }
    int getItems() const { return items; }
    double getItemsCost() const { return itemsCost; }
    Customer* getNext() const { return next; }
    void setNext(Customer* node) { next = node; }
};

int Customer::nextCustomerID = 400;

class CheckoutQueue {
private:
    Customer* head = nullptr;
    Customer* tail = nullptr;
    int lineSize = 0;
    int customersServed = 0;

public:
    ~CheckoutQueue() { clear(false); }

    bool empty() const { return head == nullptr; }
    int size() const { return lineSize; }
    int served() const { return customersServed; }

    void enqueue(int items, double cost) {
        Customer* customer = new Customer(items, cost);

        if (tail == nullptr) {
            head = tail = customer;
        } else {
            tail->setNext(customer);
            tail = customer;
        }

        ++lineSize;
        std::cout << "Customer " << customer->getCustomerID()
                  << " entered with " << items << " item(s), worth $"
                  << std::fixed << std::setprecision(2) << cost << ".\n";
    }

    bool dequeue() {
        if (empty()) {
            std::cout << "No customer can leave because the checkout line is empty.\n";
            return false;
        }

        Customer* departing = head;
        head = head->getNext();
        if (head == nullptr) tail = nullptr;

        std::cout << "Customer " << departing->getCustomerID()
                  << " completed checkout.\n";

        delete departing;
        --lineSize;
        ++customersServed;
        return true;
    }

    void print() const {
        if (empty()) {
            std::cout << "\nThe checkout line is empty.\n"
                      << "Customers served: " << customersServed << "\n";
            return;
        }

        std::cout << "\nCurrent Checkout Lane\n";
        std::cout << std::left << std::setw(20) << "Position"
                  << std::setw(12) << "Customer ID"
                  << std::right << std::setw(12) << "Items"
                  << std::setw(18) << "Items Cost ($)" << '\n';

        const Customer* current = head;
        int position = 0;
        int totalItems = 0;
        double totalCost = 0.0;

        while (current != nullptr) {
            std::string label;
            if (current == head && current == tail) label = "Head & Tail";
            else if (current == head) label = "Head";
            else if (current == tail) label = "Tail";
            else label = std::to_string(position);

            std::cout << std::left << std::setw(20) << label
                      << std::setw(12) << current->getCustomerID()
                      << std::right << std::setw(12) << current->getItems()
                      << std::fixed << std::setprecision(2)
                      << std::setw(18) << current->getItemsCost() << '\n';

            totalItems += current->getItems();
            totalCost += current->getItemsCost();
            current = current->getNext();
            ++position;
        }

        std::cout << "\nCustomers in line: " << lineSize
                  << "\nCustomers served: " << customersServed
                  << "\nTotal items waiting: " << totalItems
                  << "\nTotal item value: $" << std::fixed
                  << std::setprecision(2) << totalCost << "\n";
    }

    void clear(bool resetServed = true) {
        while (head != nullptr) {
            Customer* current = head;
            head = head->getNext();
            delete current;
        }

        tail = nullptr;
        lineSize = 0;
        if (resetServed) customersServed = 0;
    }
};

int readInteger(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) return value;

        std::cout << "Invalid number. Try again.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
}

void runSimulation(CheckoutQueue& queue, int cycles, std::mt19937& generator) {
    std::uniform_int_distribution<int> action(1, 3);
    std::uniform_int_distribution<int> itemCount(1, 200);
    std::uniform_real_distribution<double> itemCost(10.00, 1000.00);

    std::cout << "\nRunning " << cycles << " simulation cycle(s)...\n";

    for (int cycle = 1; cycle <= cycles; ++cycle) {
        std::cout << "[" << cycle << "] ";

        if (action(generator) <= 2) {
            queue.enqueue(itemCount(generator), itemCost(generator));
        } else {
            queue.dequeue();
        }
    }
}

int menu(int cycles) {
    std::cout << "\nCheckered Checkouts Simulation\n"
              << "1 - Set simulation cycles (currently " << cycles << ")\n"
              << "2 - Run simulation\n"
              << "3 - Print checkout line\n"
              << "4 - Clear checkout line\n"
              << "0 - Exit\n";

    return readInteger("Option: ");
}

int main() {
    CheckoutQueue queue;
    int cycles = 10;
    std::random_device device;
    std::mt19937 generator(device());

    std::cout << "Welcome to Checkered Checkouts\n";

    int option;
    while ((option = menu(cycles)) != 0) {
        switch (option) {
            case 1: {
                int requested = readInteger("Enter simulation cycles (1-2000): ");
                if (requested >= 1 && requested <= 2000) {
                    cycles = requested;
                    std::cout << "Simulation cycles set to " << cycles << ".\n";
                } else {
                    std::cout << "Cycles must be between 1 and 2000.\n";
                }
                break;
            }
            case 2:
                runSimulation(queue, cycles, generator);
                break;
            case 3:
                queue.print();
                break;
            case 4:
                queue.clear();
                std::cout << "Checkout line cleared.\n";
                break;
            default:
                std::cout << "Unknown option.\n";
        }
    }

    std::cout << "End of Checkered Checkouts.\n";
}
