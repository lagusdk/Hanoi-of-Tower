#include "std_lib_facilities.h" // 헤더 파일

// 규칙에 따라 원반 옮길 수 있는지 여부 판단 함수
bool IsMoveAllowed(const vector<vector<int>>& towers, int From, int To) {
    
    if (From < 0 || To < 0 || From >= towers.size() || To >= towers.size()) { // 조건 1. 인덱스 범위 확인
        cout << "올바른 범위 내의 기둥을 지정해주세요! \n";
        return false;
    }

    if (From == To) { // 조건 2. 동일한 기둥으로의 이동 확인
        cout << "동일한 기둥으로 원반을 옮길 수 없습니다! \n";
        return false;
    }

    if(towers[From].empty()) { // 조건 3. from에 원반이 없고 비어있으면 규칙위반
        cout << "옮기고자 하는 기둥에 원반이 없습니다! \n";
        return false;
    }

    if(!towers[To].empty() && towers[From].back() > towers[To].back()) { // 조건 4. to가 꽉차있거나 from의 작은 원반 위에 to의 큰 원반을 올린다면 규칙위반
        cout << "작은 원반 위에 큰 원반을 올릴 수 없습니다! \n";
        return false;
    }

    return true; // 이동 가능
}
    
// 퍼즐 다 풀었는지 확인하는 함수
bool IsPuzzleSolved(const vector<vector<int>>& towers, int beRod, int beDisk) {
    if (towers[beRod - 1].size() != beDisk) return false; // 마지막 기둥의 원반 수 = beDisk 확인
    for (int i = 0; i < towers[beRod - 1].size() - 1; ++i) { // 조건 4 만족 여부 확인
        if (towers[beRod - 1][i] < towers[beRod - 1][i + 1]) return false;
    }
    return true;
}

// 타워의 현재 상태 출력하는 함수 생성
void TowerStatus(const vector<vector<int>>& towers, int PlayCount) {
    cout << "\n◆ " << PlayCount << " : Current Status ◆ \n";
    for (int i = 0; i < towers.size(); ++i) { // 각 기둥에 대해서 반복
        cout << "[" << i + 1 << "] ";
        for (int disk : towers[i]) { // 범위 기반의 for문
                                     // disk : tower[i] 벡터의 각 원소(원반)
            cout << disk << " "; // 원반의 크기 출력(공백으로 구분)
        }
        cout << "\n";
    }
}

// 원반 옮기는 함수
void MoveDisk(vector<vector<int>>& towers, int From, int To) {
    towers[To].push_back(towers[From].back()); // 목적지 막대의 가장 위에 출발지 막대의 원반을 추가
    towers[From].pop_back(); // 출발지 막대의 가장 위에 있는 원반을 제거한다.
}

// 이동할 기둥 선택지 출력 함수
void PrintRod(const vector<int>& Rnum) {
    cout << "[";
    for (unsigned int i = 0; i < Rnum.size(); i++) {
        cout << Rnum[i]; // 숫자 출력
        if (i < Rnum.size() - 1) cout << "]["; // 마지막 숫자가 아니면 "][" 추가
    }
    cout << "]";
}

// 난이도 설정 후 퍼즐 진행 함수
void PlayPuzzle(int beDisk, int beRod) {
    vector<vector<int>> towers(beRod); // 플레이어가 설정한 개수만큼의 기둥
    for (int disk = beDisk; disk > 0; --disk) { // 첫번째 막대에 플레이어가 설정한 만큼의 n부터 1까지의 원반 역순 추가
        towers[0].push_back(disk);
    }

    int PlayCount = 0; // 이동횟수 초기화..

    while (true) { // 퍼즐루프 무한반복
        TowerStatus(towers, ++PlayCount); // 현재 타워 상태 출력

        vector<int> Rnum; // 숫자들을 저장할 벡터
        for (int i = 1; i <= beRod; i++) {
            Rnum.push_back(i);
        }

        cout << "\n" << PlayCount << "번째 실행. 몇 번째 기둥(Rod)에서 몇 번째 기둥(Rod)로 원반을 이동시키겠습니까? \n(From = ";
        PrintRod(Rnum); 
        cout << ", To = ";
        PrintRod(Rnum);
        cout << ") : ";
        
        int From, To; // 이동의 시작 및 끝 기둥 위치 변수
        cin >> From >> To; 
        --From; --To; 

        if (IsMoveAllowed(towers, From, To)) {
            MoveDisk(towers, From, To); // 원반 이동 후 메시지 출력
            cout << "→ " << From + 1 << "번째 기둥(Rod)에서 " << To + 1 << "번째 기둥(Rod)으로 성공적으로 원반을 옮겼습니다!\n";
        }
        else {
            cout << "→ 원반을 옮길 수 없습니다! 입력한 값을 확인해주세요! \n";
        }
        
        if (IsPuzzleSolved(towers, beRod, beDisk)) { // 퍼즐 완료 여부 확인
            TowerStatus(towers, ++PlayCount);
            cout << "\n축하합니다! " << PlayCount-1 << "번 만에 퍼즐을 성공적으로 풀었어요!\n다시 플레이하시겠습니까 ? ([1] Yes, [2] No) : ";
            int Finish;
            while (true) { // 무한 반복
                cin >> Finish;
                cout << "\n";
                if (Finish == 1) {
                    return; // 함수 종료 및 main 함수로 복귀
                }
                else if (Finish == 2) {
                    cout << "퍼즐을 종료합니다.\n";
                    exit(0); // 프로그램 종료
                }
                else {
                    cout << "다시 입력해주세요 ([1] Yes, [2] No) : "; // 잘못된 입력 처리
                }
            }
        } 
    }
}

// 프로그램 실행 및 종료
int main() {
    while (true) {
        // 난이도 설정
        int beDisk, beRod;
        
        cout << "난이도를 설정해볼까요?\n1. 원반(Disk)의 개수를 정해주세요: ";
        while (!(cin >> beDisk) || beDisk <= 0) {
            if (cin.fail()) { // 입력이 숫자가 아닌 경우
                cin.clear(); // 오류 플래그 클리어
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 버퍼 비우기
            }
            cout << "유효한 숫자를 입력해주세요: ";
        }
        cout << "2. 기둥(Rod)의 개수를 정해주세요: ";
        while (!(cin >> beRod) || beRod <= 0) {
            if (cin.fail()) { // 입력이 숫자가 아닌 경우
                cin.clear(); // 오류 플래그 클리어
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 버퍼 비우기
            }
            cout << "유효한 숫자를 입력해주세요: ";
        }

        PlayPuzzle(beDisk, beRod);
    }

    keep_window_open();
    return 0;
   
}