#include "Student.h"
#include "queue.h"
#include <queue>


int convertstringtoint(string s1)
{
    int res = 0;
    int curr = 0;
    int idx = 0;

    bool firstnonzero = 0;
    while (s1[idx] != '\0')
    {
        if (s1[idx] != '0')
            firstnonzero = 1;

        if (s1[idx] == ' ' || s1[idx] == '-')
        {
            idx++;
            continue;
        }
        if (!firstnonzero)
        {
            idx++;
            continue;
        }


        curr = s1[idx] - '0';
        res += curr;
        idx++;
        if (s1[idx] != '\0')
        {
            if (!res)
                res = 1;
            res *= 10;
        }

    }

    return res;


}



struct Quiz2
{
    string* names;
    string* ids;
    int* marks;
    int num;
    Quiz2()
    {
        names = ids = nullptr;
        marks = nullptr;
        num = 0;
    }
    void print()
    {
        for (int i = 0; i < num; i++)
        {
            cout << "Student: " << names[i];
            cout << "ID: " << ids[i] << " obtained marks -> " << marks[i]<<endl;
        }
        cout << endl;
        cin.ignore();
        cin.ignore();
        
    }
    void addStudent(string n, string i, int m)
    {        
        string* newName = new string[num+1];
        string* nids = new string[num+1];
        int* newMarks = new int[num + 1];
        for (int i = 0; i < num; i++)
        {
            newName[i] = names[i];
            nids[i] = ids[i];
            newMarks[i] = marks[i];
        }
        newName[num] = n;
        nids[num] = i;
        newMarks[num] = m;
        num++;

        this->ids = nids;
        this->marks = newMarks;
        this->names = newName;
        
    
    }

    double average()
    {
        double res=0;
        for (int i = 0; i < num; i++)
        {
            res += marks[i];
        }
        return res / num;
    
    }

    int highest()
    {
        int val = 0;
        string name = "";
        string id = "";
        for (int i = 0; i < num; i++)
        {
            if (marks[i] > val)
            {
                val = marks[i];
                name = names[i];
                id = ids[i];
            }
        
        }
        
        cout << "Highest marks-> " << val << endl;
        if (val)
        {
            cout << "Student-> " << name;
            cout << "\nID-> " << id << endl;
        }
        return val;

    }
    

    void readDataFromFile(string filename = "Quiz1.txt") {
        //string filename = "s";
        ifstream file(filename);
        if (!file.is_open()) {
            cout << "Could not open the file!\n";
            return;
        }

        string line;
        string id;
        string name;
        string marks;
        while (getline(file, line))
        {
            Student curr;
            bool firstchar = 0;
            bool err = 0;
            //currline += '\0';
            id = "";
            name = "";
            marks = "";
            int idx = 0;
            if (line[0] == '!') //Designated as a comment
                continue;
            if (line[0] == '\0') //empty lines
                continue;

            while (line[idx] != ',')
            {
                if (line[idx] != ' ' || line[idx] != '\t')
                {
                    firstchar = 1;

                }
                if (!firstchar)
                {
                    idx++;
                    continue;
                }
                id += line[idx];
                idx++;

                if (line[idx] == '\0')
                {
                    cout << "ERROR, standard not followed";
                    err = 1;
                    continue;
                }

            }
            idx++; //skipping the ,
            firstchar = 0;
            while (line[idx] != ',')
            {
                if (line[idx] != ' ' && line[idx] != '\t')
                {
                    firstchar = 1;

                }
                if (!firstchar)
                {
                    idx++;
                    continue;
                }
                if (line[idx] == '\0')
                {
                    cout << "ERROR, standard not followed";
                    err = 1;
                    continue;
                }
                name += line[idx];
                idx++;
            }
            idx++;
            while (line[idx] != '\0')
            {
                if (line[idx] != ' ' && line[idx] != '\t')
                {
                    firstchar = 1;

                }
                if (!firstchar)
                {
                    idx++;
                    continue;
                }
                if (line[idx] < '0' && line[idx]> '9')
                {
                    err = 1;
                }
                marks += line[idx];
                idx++;
            }

            if (err)
                return;

            //curr.setID(id);
            //curr.setName(name);
            int res = convertstringtoint(marks);
            this->addStudent(name, id, res);





        }

    }


};




struct Quiz {
  int marks;
  Student student;
  Quiz *left, *right, *parent;

  Quiz(int val, Student s = Student())
      : marks(val), student(s), left(nullptr), right(nullptr), parent(nullptr) {
  }
};




class QuizHeap {
public:
  QuizHeap() : root(nullptr), lastInserted(nullptr) {}

  void insert(int marks, Student &S1) {
    Quiz *newNode = new Quiz(marks);
    newNode->student = S1;
    if (root == nullptr) {
      root = newNode;
      lastInserted = newNode;
    } else {
      Quiz *parent = findParentForInsertion();
      newNode->parent = parent;
      if (parent->left == nullptr) {
        parent->left = newNode;
      } else {
        parent->right = newNode;
      }
      lastInserted = newNode;
      heapifyUp(newNode);
    }
  }

  int extractMax() {
    if (root == nullptr) {
      std::cout << "Empty" << std::endl;
      return 0;
    }

    int maxValue = root->marks;
    if (root == lastInserted) {
      //delete root;
      root = nullptr;
      lastInserted = nullptr;
    } else {
      root->marks = lastInserted->marks;
      Quiz *parent = lastInserted->parent;
      if (parent->right == lastInserted) {
        //delete parent->right;
        parent->right = nullptr;
      } else {
        //delete parent->left;
        parent->left = nullptr;
      }
      lastInserted = findLastInserted();
      heapifyDown(root);
    }

    return maxValue;
  }

  int getMax() const {
    if (root == nullptr) {
      std::cout << "Empty" << std::endl;
      return 0;
    }

    return root->marks;
  }

  bool isEmpty() const { return root == nullptr; }

  void print() const {
    if (root == nullptr) {
      std::cout << "Heap is empty" << std::endl;
    } else {
      printInOrder(root);
      std::cout << std::endl;
    }
  }

  void readDataFromFile(string filename = "Quiz1.txt") {
    //string filename = "s";
    ifstream file(filename);
    if (!file.is_open()) {
      cout << "Could not open the file!\n";
      return;
    }

    string line;
    string id;
    string name;
    string marks;
    while (getline(file, line))
    {
        Student curr;
        bool firstchar = 0;
        bool err = 0;
        //currline += '\0';
        id = "";
        name = "";
        int idx = 0;
        if (line[0] == '!') //Designated as a comment
            continue;
        if (line[0] == '\0') //empty lines
            continue;

        while (line[idx] != ',')
        {
            if (line[idx] != ' '||line[idx]!='\t')
            {
                firstchar = 1;
                
            }
            if (!firstchar)
            {
                idx++;
                continue;
            }
            id += line[idx];
            idx++;

            if (line[idx] == '\0')
            {
                cout << "ERROR, standard not followed";
                err = 1;
                continue;
            }

        }
        idx++; //skipping the ,
        firstchar = 0;
        while (line[idx] != ',')
        {
            if (line[idx] != ' ' && line[idx] != '\t')
            {
                firstchar = 1;

            }
            if (!firstchar)
            {
                idx++;
                continue;
            }
            if (line[idx] == '\0')
            {
                cout << "ERROR, standard not followed";
                err = 1;
                continue;
            }
            name += line[idx];
            idx++;
        }
        idx++;
        while (line[idx] != '\0')
        {
            if (line[idx] != ' ' && line[idx] != '\t')
            {
                firstchar = 1;

            }
            if (!firstchar)
            {
                idx++;
                continue;
            }
            if (line[idx] < '0' && line[idx]> '9')
            {
                err = 1;
            }
            marks += line[idx];
            idx++;
        }

        if (err)
            return;

        curr.setID(id);
        curr.setName(name);
        int res = convertstringtoint(marks);
        this->insert(res, curr);





    }
    
  }

public:
  Quiz *root;
  Quiz *lastInserted;

  void heapifyUp(Quiz *quiz) {
    while (quiz->parent != nullptr && quiz->marks > quiz->parent->marks) {
      std::swap(quiz->marks, quiz->parent->marks);
      quiz = quiz->parent;
    }
  }

  void heapifyDown(Quiz *quiz) {
    while (quiz != nullptr) {
      Quiz *largest = quiz;
      if (quiz->left != nullptr && quiz->left->marks > largest->marks) {
        largest = quiz->left;
      }
      if (quiz->right != nullptr && quiz->right->marks > largest->marks) {
        largest = quiz->right;
      }
      if (largest != quiz) {
        std::swap(quiz->marks, largest->marks);
        quiz = largest;
      } else {
        break;
      }
    }
  }

  Quiz *findParentForInsertion() {
    queue<Quiz *> q;
    q.push(root);
    while (!q.empty()) {
      Quiz *quiz = q.front();
      q.pop();
      if (quiz->left == nullptr || quiz->right == nullptr) {
        return quiz;
      }
      q.push(quiz->left);
      q.push(quiz->right);
    }
    return nullptr;
  }

  Quiz *findLastInserted() {
    queue<Quiz *> q;
    q.push(root);
    Quiz *last = nullptr;
    while (!q.empty()) {
      last = q.front();
      q.pop();
      if (last->left != nullptr) {
        q.push(last->left);
      }
      if (last->right != nullptr) {
        q.push(last->right);
      }
    }
    return last;
  }

  void printInOrder(Quiz *StudentNode) const {
    if (StudentNode == nullptr) {
      return;
    }
    printInOrder(StudentNode->left);
    cout << StudentNode->student.getName() << '(' << StudentNode->student.getID() << "): " << StudentNode->marks<<'\n';
    printInOrder(StudentNode->right);
  }

  int sum(Quiz * root)
  {
      if (root == nullptr) {
          return 0;
      }
      
      return root->marks + sum(root->left) + sum(root->right);
  
  }

  int count(Quiz* root)
  {
      if (root == nullptr)
      {
          return 0;
      }

      return 1 + sum(root->left) + sum(root->right);
  
  }

  double average()
  {
      int Sum = sum(root);
      int Count = count(root);

      double avg = Sum;
      return avg / Count;

  }



  void calculateSumAndCount(Quiz* root, int& sum, int& count) {
      if (!root) return;

      Queue<Quiz*> q;
      q.enqueue(root);

      while (!q.isEmpty()) {
          Quiz* current = q.getFront();
          q.dequeue();

          sum += current->marks;
          count++;

          if (current->left) q.enqueue(current->left);
          if (current->right) q.enqueue(current->right);
      }
  }

  // Function to find the average of values of all nodes
  double findAverage(Quiz* root) {
      if (!root) return 0.0;

      int sum = 0;
      int count = 0;

      calculateSumAndCount(root, sum, count);

      return static_cast<double>(sum) / count;
  }



};
