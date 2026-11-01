#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

std::string toLowerStr(std::string str) {
    for (size_t i = 0; i < str.length(); ++i) {
        str[i] = std::tolower(str[i]);
    }
    return str;
}

std::string normalizeVehicleType(std::string type) {
    std::string lower = toLowerStr(type);
    if (lower == "car") return "Car";
    if (lower == "motorcycle") return "Motorcycle";
    if (lower == "bicycle") return "Bicycle";
    return "";
}

class Vehicle {
private:
    int vehicleID;
    std::string vehicleType; 
    int entryTime;   
    int parkingDuration;  
    double parkingFee;   
    bool isOccupied;  

public:
    Vehicle() 
        : vehicleID(0), vehicleType(""), entryTime(0), parkingDuration(0), parkingFee(0.0), isOccupied(false) {}

    Vehicle(int id, std::string type, int time, int duration)
        : vehicleID(id), entryTime(time), parkingDuration(duration), parkingFee(0.0), isOccupied(true) {
        vehicleType = normalizeVehicleType(type);
        calculateFee();
    }

    int getVehicleID() const { return vehicleID; }
    std::string getVehicleType() const { return vehicleType; }
    int getEntryTime() const { return entryTime; }
    int getParkingDuration() const { return parkingDuration; }
    double getParkingFee() const { return parkingFee; }
    bool getIsOccupied() const { return isOccupied; }

    void setVehicleID(int id) { vehicleID = id; }
    void setVehicleType(std::string type) { vehicleType = normalizeVehicleType(type); }
    void setEntryTime(int time) { entryTime = time; }
    void setParkingDuration(int duration) { parkingDuration = duration; }
    void setParkingFee(double fee) { parkingFee = fee; }
    void setIsOccupied(bool occupied) { isOccupied = occupied; }

    void calculateFee() {
        if (!isOccupied) {
            parkingFee = 0.0;
            return;
        }

        double baseRate = 0.0;
        if (vehicleType == "Car") baseRate = 6.0;
        else if (vehicleType == "Motorcycle") baseRate = 4.0;
        else if (vehicleType == "Bicycle") baseRate = 2.0;

        bool isPeak = (entryTime >= 6 && entryTime <= 9) || (entryTime >= 15 && entryTime <= 18);

        double rateFirst2Hours = isPeak ? (baseRate * 1.30) : (baseRate * 0.95);
        double rateFromHour3 = baseRate * 0.90;

        if (parkingDuration <= 2) {
            parkingFee = parkingDuration * rateFirst2Hours;
        } else {
            parkingFee = (2 * rateFirst2Hours) + ((parkingDuration - 2) * rateFromHour3);
        }
    }

    void display() const {
        if (!isOccupied) return;
        std::cout << "  - ID Xe: " << std::setw(6) << vehicleID
                  << " | Loại: " << std::setw(11) << vehicleType
                  << " | Giờ vào: " << std::setw(2) << entryTime << ":00"
                  << " | Thời lượng: " << std::setw(2) << parkingDuration << "h"
                  << " | Phí: $" << std::fixed << std::setprecision(2) << parkingFee << "\n";
    }
};

class ParkingLot {
private:
    int parkID;
    char size;
    
    Vehicle vehicle1;
    Vehicle vehicle2;
    Vehicle vehicle3;

    bool hasVehicle1;
    bool hasVehicle2;
    bool hasVehicle3;

public:
    ParkingLot() 
        : parkID(0), size('S'), hasVehicle1(false), hasVehicle2(false), hasVehicle3(false) {}

    ParkingLot(int id, char s) 
        : parkID(id), size(std::toupper(s)), hasVehicle1(false), hasVehicle2(false), hasVehicle3(false) {}

    int getParkID() const { return parkID; }
    char getSize() const { return size; }
    void setParkID(int id) { parkID = id; }
    void setSize(char s) { size = std::toupper(s); }

    int getMaxCapacity() const {
        if (size == 'S') return 1;
        if (size == 'M') return 2;
        if (size == 'L') return 3;
        return 0;
    }

    int getCurrentCount() const {
        int count = 0;
        if (hasVehicle1) count++;
        if (hasVehicle2) count++;
        if (hasVehicle3) count++;
        return count;
    }

    bool isFull() const {
        return getCurrentCount() >= getMaxCapacity();
    }

    bool containsVehicle(int vID) const {
        if (hasVehicle1 && vehicle1.getVehicleID() == vID) return true;
        if (hasVehicle2 && vehicle2.getVehicleID() == vID) return true;
        if (hasVehicle3 && vehicle3.getVehicleID() == vID) return true;
        return false;
    }

    bool addVehicle(const Vehicle& v) {
        if (isFull()) return false;

        int capacity = getMaxCapacity();
        if (capacity >= 1 && !hasVehicle1) {
            vehicle1 = v;
            hasVehicle1 = true;
            return true;
        }
        if (capacity >= 2 && !hasVehicle2) {
            vehicle2 = v;
            hasVehicle2 = true;
            return true;
        }
        if (capacity >= 3 && !hasVehicle3) {
            vehicle3 = v;
            hasVehicle3 = true;
            return true;
        }
        return false;
    }

    bool removeVehicle(int vID) {
        if (hasVehicle1 && vehicle1.getVehicleID() == vID) {
            hasVehicle1 = false;
            vehicle1.setIsOccupied(false);
            return true;
        }
        if (hasVehicle2 && vehicle2.getVehicleID() == vID) {
            hasVehicle2 = false;
            vehicle2.setIsOccupied(false);
            return true;
        }
        if (hasVehicle3 && vehicle3.getVehicleID() == vID) {
            hasVehicle3 = false;
            vehicle3.setIsOccupied(false);
            return true;
        }
        return false;
    }

    void displayLotInfo() const {
        std::cout << "[BÃI ĐỖ XE ID: " << parkID << "] - Kích thước: " << size 
                  << " (Sức chứa: " << getCurrentCount() << "/" << getMaxCapacity() << " xe)\n";
        
        if (getCurrentCount() == 0) {
            std::cout << "  (Bãi trống)\n";
            return;
        }

        if (hasVehicle1) vehicle1.display();
        if (hasVehicle2) vehicle2.display();
        if (hasVehicle3) vehicle3.display();
    }

    void listVehiclesByType(const std::string& targetType) const {
        std::string stdType = normalizeVehicleType(targetType);
        if (hasVehicle1 && vehicle1.getVehicleType() == stdType) {
            std::cout << "  - Tại Bãi ID [" << parkID << "]: ";
            vehicle1.display();
        }
        if (hasVehicle2 && vehicle2.getVehicleType() == stdType) {
            std::cout << "  - Tại Bãi ID [" << parkID << "]: ";
            vehicle2.display();
        }
        if (hasVehicle3 && vehicle3.getVehicleType() == stdType) {
            std::cout << "  - Tại Bãi ID [" << parkID << "]: ";
            vehicle3.display();
        }
    }

    void accumulateStats(const std::string& type, double& sumFee, int& count) const {
        std::string stdType = normalizeVehicleType(type);
        if (hasVehicle1 && vehicle1.getVehicleType() == stdType) {
            sumFee += vehicle1.getParkingFee();
            count++;
        }
        if (hasVehicle2 && vehicle2.getVehicleType() == stdType) {
            sumFee += vehicle2.getParkingFee();
            count++;
        }
        if (hasVehicle3 && vehicle3.getVehicleType() == stdType) {
            sumFee += vehicle3.getParkingFee();
            count++;
        }
    }

    double getTotalLotFee() const {
        double total = 0.0;
        if (hasVehicle1) total += vehicle1.getParkingFee();
        if (hasVehicle2) total += vehicle2.getParkingFee();
        if (hasVehicle3) total += vehicle3.getParkingFee();
        return total;
    }
};

class SystemInterface {
private:
    ParkingLot parkingLot1;
    ParkingLot parkingLot2;
    ParkingLot parkingLot3;

    bool hasLot1;
    bool hasLot2;
    bool hasLot3;

    bool isVehicleIDExists(int vID) const {
        if (hasLot1 && parkingLot1.containsVehicle(vID)) return true;
        if (hasLot2 && parkingLot2.containsVehicle(vID)) return true;
        if (hasLot3 && parkingLot3.containsVehicle(vID)) return true;
        return false;
    }

public:
    SystemInterface() : hasLot1(false), hasLot2(false), hasLot3(false) {}

    void createParkingLot() {
        if (hasLot1 && hasLot2 && hasLot3) {
            std::cout << "=> LỖI: Hệ thống đã đạt giới hạn tối đa (3 bãi đỗ xe)!\n";
            return;
        }

        int parkID;
        char size;
        std::cout << "Nhập ID Bãi đỗ xe: ";
        std::cin >> parkID;

        if ((hasLot1 && parkingLot1.getParkID() == parkID) ||
            (hasLot2 && parkingLot2.getParkID() == parkID) ||
            (hasLot3 && parkingLot3.getParkID() == parkID)) {
            std::cout << "=> LỖI: ID Bãi đỗ xe [" << parkID << "] đã tồn tại trong hệ thống!\n";
            return;
        }

        std::cout << "Nhập Kích thước bãi ('S' - Nhỏ, 'M' - Vừa, 'L' - Lớn): ";
        std::cin >> size;
        size = std::toupper(size);

        if (size != 'S' && size != 'M' && size != 'L') {
            std::cout << "=> LỖI: Kích thước bãi đỗ không hợp lệ! Chỉ chấp nhận 'S', 'M', hoặc 'L'.\n";
            return;
        }

        ParkingLot newLot(parkID, size);
        if (!hasLot1) {
            parkingLot1 = newLot;
            hasLot1 = true;
        } else if (!hasLot2) {
            parkingLot2 = newLot;
            hasLot2 = true;
        } else if (!hasLot3) {
            parkingLot3 = newLot;
            hasLot3 = true;
        }

        std::cout << "=> THÀNH CÔNG: Đã tạo Bãi đỗ xe ID [" << parkID << "] kích thước '" << size << "'.\n";
    }

    void addVehicleToLot() {
        if (!hasLot1 && !hasLot2 && !hasLot3) {
            std::cout << "=> LỖI: Hệ thống chưa có bãi đỗ xe nào! Vui lòng tạo bãi trước.\n";
            return;
        }

        int vID, entryTime, duration;
        std::string type;

        std::cout << "Nhập Mã phương tiện (Vehicle ID): ";
        std::cin >> vID;

        if (isVehicleIDExists(vID)) {
            std::cout << "=> LỖI: Xe có Mã ID [" << vID << "] đã tồn tại trong hệ thống!\n";
            return;
        }

        std::cout << "Nhập Loại phương tiện (Car / Motorcycle / Bicycle): ";
        std::cin >> type;
        std::string normType = normalizeVehicleType(type);
        if (normType.empty()) {
            std::cout << "=> LỖI: Loại phương tiện không hợp lệ! Chỉ nhận: Car, Motorcycle, Bicycle.\n";
            return;
        }

        std::cout << "Nhập Giờ vào bãi (0 - 23): ";
        std::cin >> entryTime;
        if (entryTime < 0 || entryTime > 23) {
            std::cout << "=> LỖI: Giờ vào bãi phải từ 0 đến 23.\n";
            return;
        }

        std::cout << "Nhập Số giờ đỗ dự kiến (1 - 23): ";
        std::cin >> duration;
        if (duration < 1 || duration > 23) {
            std::cout << "=> LỖI: Số giờ đỗ dự kiến phải từ 1 đến 23.\n";
            return;
        }

        Vehicle newVehicle(vID, normType, entryTime, duration);

        if (hasLot1 && !parkingLot1.isFull()) {
            parkingLot1.addVehicle(newVehicle);
            std::cout << "=> THÀNH CÔNG: Đã đỗ xe vào Bãi ID [" << parkingLot1.getParkID() << "].\n";
            return;
        }
        if (hasLot2 && !parkingLot2.isFull()) {
            parkingLot2.addVehicle(newVehicle);
            std::cout << "=> THÀNH CÔNG: Đã đỗ xe vào Bãi ID [" << parkingLot2.getParkID() << "].\n";
            return;
        }
        if (hasLot3 && !parkingLot3.isFull()) {
            parkingLot3.addVehicle(newVehicle);
            std::cout << "=> THÀNH CÔNG: Đã đỗ xe vào Bãi ID [" << parkingLot3.getParkID() << "].\n";
            return;
        }

        std::cout << "=> LỖI: Rất tiếc, tất cả các bãi đỗ xe hiện tại đều đã ĐẦY!\n";
    }

    void removeLot() {
        int parkID;
        std::cout << "Nhập ID Bãi đỗ xe cần xóa: ";
        std::cin >> parkID;

        if (hasLot1 && parkingLot1.getParkID() == parkID) {
            hasLot1 = false;
            std::cout << "=> THÀNH CÔNG: Đã xóa Bãi đỗ xe ID [" << parkID << "] khỏi hệ thống.\n";
            return;
        }
        if (hasLot2 && parkingLot2.getParkID() == parkID) {
            hasLot2 = false;
            std::cout << "=> THÀNH CÔNG: Đã xóa Bãi đỗ xe ID [" << parkID << "] khỏi hệ thống.\n";
            return;
        }
        if (hasLot3 && parkingLot3.getParkID() == parkID) {
            hasLot3 = false;
            std::cout << "=> THÀNH CÔNG: Đã xóa Bãi đỗ xe ID [" << parkID << "] khỏi hệ thống.\n";
            return;
        }

        std::cout << "=> LỖI: Không tìm thấy Bãi đỗ xe có ID [" << parkID << "].\n";
    }

    void removeVehicleFromSystem() {
        int vID;
        std::cout << "Nhập Mã phương tiện (Vehicle ID) cần lấy ra: ";
        std::cin >> vID;

        if (hasLot1 && parkingLot1.removeVehicle(vID)) {
            std::cout << "=> THÀNH CÔNG: Đã lấy xe ID [" << vID << "] ra khỏi Bãi ID [" << parkingLot1.getParkID() << "].\n";
            return;
        }
        if (hasLot2 && parkingLot2.removeVehicle(vID)) {
            std::cout << "=> THÀNH CÔNG: Đã lấy xe ID [" << vID << "] ra khỏi Bãi ID [" << parkingLot2.getParkID() << "].\n";
            return;
        }
        if (hasLot3 && parkingLot3.removeVehicle(vID)) {
            std::cout << "=> THÀNH CÔNG: Đã lấy xe ID [" << vID << "] ra khỏi Bãi ID [" << parkingLot3.getParkID() << "].\n";
            return;
        }

        std::cout << "=> LỖI: Không tìm thấy phương tiện có Mã ID [" << vID << "] trong bãi.\n";
    }

    void displayAllLots() const {
        std::cout << "\n========== DANH SÁCH TẤT CẢ BÃI ĐỖ XE ==========\n";
        if (!hasLot1 && !hasLot2 && !hasLot3) {
            std::cout << "Hệ thống chưa có bãi đỗ xe nào.\n";
            return;
        }

        if (hasLot1) {
            std::cout << "• Bãi ID: " << std::setw(4) << parkingLot1.getParkID()
                      << " | Kích thước: " << parkingLot1.getSize()
                      << " | Xe hiện có: " << parkingLot1.getCurrentCount() << "/" << parkingLot1.getMaxCapacity() << "\n";
        }
        if (hasLot2) {
            std::cout << "• Bãi ID: " << std::setw(4) << parkingLot2.getParkID()
                      << " | Kích thước: " << parkingLot2.getSize()
                      << " | Xe hiện có: " << parkingLot2.getCurrentCount() << "/" << parkingLot2.getMaxCapacity() << "\n";
        }
        if (hasLot3) {
            std::cout << "• Bãi ID: " << std::setw(4) << parkingLot3.getParkID()
                      << " | Kích thước: " << parkingLot3.getSize()
                      << " | Xe hiện có: " << parkingLot3.getCurrentCount() << "/" << parkingLot3.getMaxCapacity() << "\n";
        }
    }

    void displaySpecificLot() const {
        int parkID;
        std::cout << "Nhập ID Bãi đỗ xe cần xem chi tiết: ";
        std::cin >> parkID;

        std::cout << "\n--- CHI TIẾT BÃI ĐỖ XE ---\n";
        if (hasLot1 && parkingLot1.getParkID() == parkID) {
            parkingLot1.displayLotInfo();
            return;
        }
        if (hasLot2 && parkingLot2.getParkID() == parkID) {
            parkingLot2.displayLotInfo();
            return;
        }
        if (hasLot3 && parkingLot3.getParkID() == parkID) {
            parkingLot3.displayLotInfo();
            return;
        }

        std::cout << "=> LỖI: Không tìm thấy Bãi đỗ xe có ID [" << parkID << "].\n";
    }

    void listVehiclesByType() const {
        std::string type;
        std::cout << "Nhập Loại phương tiện cần lọc (Car / Motorcycle / Bicycle): ";
        std::cin >> type;

        std::string stdType = normalizeVehicleType(type);
        if (stdType.empty()) {
            std::cout << "=> LỖI: Loại phương tiện không hợp lệ!\n";
            return;
        }

        std::cout << "\n--- DANH SÁCH XE LOẠI [" << stdType << "] TRONG HỆ THỐNG ---\n";
        if (hasLot1) parkingLot1.listVehiclesByType(stdType);
        if (hasLot2) parkingLot2.listVehiclesByType(stdType);
        if (hasLot3) parkingLot3.listVehiclesByType(stdType);
    }

    void displayFeeReport() const {
        std::cout << "\n================ BÁO CÁO PHÍ ĐỖ XE ================\n";
        
        std::string types[3] = {"Car", "Motorcycle", "Bicycle"};
        std::cout << "1. PHÍ ĐỖ XE TRUNG BÌNH THEO LOẠI XE (TOÀN HỆ THỐNG):\n";

        for (int i = 0; i < 3; ++i) {
            double totalFee = 0.0;
            int count = 0;

            if (hasLot1) parkingLot1.accumulateStats(types[i], totalFee, count);
            if (hasLot2) parkingLot2.accumulateStats(types[i], totalFee, count);
            if (hasLot3) parkingLot3.accumulateStats(types[i], totalFee, count);

            std::cout << "  • Loại " << std::setw(11) << types[i] << ": ";
            if (count > 0) {
                std::cout << "$" << std::fixed << std::setprecision(2) << (totalFee / count)
                          << " (Số lượng: " << count << " xe, Tổng phí: $" << totalFee << ")\n";
            } else {
                std::cout << "N/A (Chưa có xe nào đỗ)\n";
            }
        }

        std::cout << "\n2. PHÂN TÍCH CHI TIẾT THEO TỪNG BÃI ĐỖ XE:\n";
        if (!hasLot1 && !hasLot2 && !hasLot3) {
            std::cout << "  (Chưa có bãi đỗ xe nào trong hệ thống)\n";
            return;
        }

        auto printLotReport = [](const ParkingLot& lot) {
            int count = lot.getCurrentCount();
            double totalFee = lot.getTotalLotFee();
            std::cout << "  • Bãi ID [" << lot.getParkID() << "] (Size " << lot.getSize() << "): "
                      << "Tổng phí: $" << std::fixed << std::setprecision(2) << totalFee;
            if (count > 0) {
                std::cout << " | Trực thuộc " << count << " xe | Phí TB: $" << (totalFee / count) << "\n";
            } else {
                std::cout << " | Bãi trống | Phí TB: N/A\n";
            }
        };

        if (hasLot1) printLotReport(parkingLot1);
        if (hasLot2) printLotReport(parkingLot2);
        if (hasLot3) printLotReport(parkingLot3);
    }

    void runMenu() {
        int choice = 0;
        do {
            std::cout << "\n==================================================\n";
            std::cout << "         HỆ THỐNG QUẢN LÝ BÃI ĐỖ XE (PARKING)      \n";
            std::cout << "==================================================\n";
            std::cout << " 1. Tạo Bãi đỗ xe mới\n";
            std::cout << " 2. Thêm xe vào bãi đỗ xe\n";
            std::cout << " 3. Xóa một Bãi đỗ xe\n";
            std::cout << " 4. Lấy xe ra khỏi bãi đỗ\n";
            std::cout << " 5. Hiển thị danh sách tất cả các Bãi đỗ xe\n";
            std::cout << " 6. Hiển thị danh sách xe theo bãi cụ thể\n";
            std::cout << " 7. Liệt kê xe theo loại phương tiện\n";
            std::cout << " 8. Xem báo cáo tóm tắt phí đỗ xe trung bình\n";
            std::cout << " 9. Thoát chương trình\n";
            std::cout << "--------------------------------------------------\n";
            std::cout << "Lựa chọn của bạn (1-9): ";
            
            if (!(std::cin >> choice)) {
                std::cin.clear();
                std::string dummy;
                std::cin >> dummy;
                std::cout << "=> LỖI: Nhập sai định dạng, vui lòng thử lại.\n";
                continue;
            }

            switch (choice) {
                case 1: createParkingLot(); break;
                case 2: addVehicleToLot(); break;
                case 3: removeLot(); break;
                case 4: removeVehicleFromSystem(); break;
                case 5: displayAllLots(); break;
                case 6: displaySpecificLot(); break;
                case 7: listVehiclesByType(); break;
                case 8: displayFeeReport(); break;
                case 9:
                    std::cout << "=> Cảm ơn bạn đã sử dụng hệ thống. Tạm biệt!\n";
                    break;
                default:
                    std::cout << "=> LỖI: Lựa chọn không hợp lệ. Vui lòng chọn từ 1 đến 9.\n";
                    break;
            }
        } while (choice != 9);
    }
};

int main() {
    SystemInterface app;
    app.runMenu();
    return 0;
}