//
// Created by msmkl on 27.02.2023.
//

#include <iostream>
#include <list>
#include <set>
#include <fstream>
#include <string>
#include <sstream>
#include <cmath>
#include <vector>

using namespace std;

typedef std::common_type<int>::type NumericType;


template <class T1>
class Node{
public:
    T1 value;
    string name;

    bool operator<(const Node& rhs) const {
        return (value < rhs.value);
    }



};

//template <class T1>
//bool operator==(const Node<T1>& lhs, const Node<T1>& rhs){
//
//        return (typeid(lhs.name) == typeid(rhs.name));
//
//    }


template <class T1, class T2>
class Graph{

private:


public:
    set<Node<T1>> nodes_;
    list< pair< pair< Node<T1>, Node<T1> >, T2 > > edges_;


    Graph():edges_(), nodes_(){}

    Graph(Graph<T1, T2> & obj) {
        copy(obj.edges_.begin(), obj.edges_.end(), std::back_inserter(edges_));
        nodes_.insert(obj.nodes_.begin(), obj.nodes_.end());
    }

    Graph(Graph<T1, T2> && obj) noexcept{
        nodes_.clear();
        edges_.clear();
        for(auto it = obj.edges_.begin(); it != obj.edges_.end(); ++it){
            edges_.push_back(*it);

        }
        for(auto it = obj.nodes_.begin(); it != obj.nodes_.end(); ++it){
            nodes_.insert(*it);

        }
        obj.nodes_.clear();
        obj.edges_.clear();

    }


    Graph & operator = (const Graph<T1, T2> & obj){
        if (this == &obj){
            return *this;
        }
        edges_.clear();
        copy(obj.edges_.begin(), obj.edges_.end(), std::back_inserter(edges_));
        nodes_.insert(obj.nodes_.begin(), obj.nodes_.end());
        return *this;
    }

    Graph & operator = ( Graph<T1, T2> && obj) noexcept {
        if (this == &obj){
            return *this;
        }
        nodes_.clear();
        edges_.clear();
        for(auto it = obj.edges_.begin(); it != obj.edges_.end(); ++it){
            edges_.push_back(*it);

        }
        for(auto it = obj.nodes_.begin(); it != obj.nodes_.end(); ++it){
            nodes_.insert(*it);

        }
        obj.nodes_.clear();
        obj.edges_.clear();
        return *this;
    }



    void makeEdge(Node<T1> A, Node<T1> B, T2 W){
        edges_.push_back(make_pair(make_pair(A, B), W));
        nodes_.insert(A);
        nodes_.insert(B);

    }

    void info_structure(){
        cout << "________________STRUCTURE________________" << endl;
        for(auto i = edges_.begin(); i!= edges_.end(); i++){
            cout << '\t' << '\t' << i->first.first.name << " --> " << i->first.second.name << endl;
        }
        cout << endl;
    }

    void info_weights_and_vertex(){
        cout << "___________________WEIGHTS___________________" << endl;
        for(auto i = edges_.begin(); i!= edges_.end(); i++){
            cout << '\t' << '\t' << i->first.first.name << "{" <<  i->first.first.value <<  "}"  << " ----" << i->second<< "----> " << i->first.second.name << "{" <<  i->first.second.value <<  "}" << endl;
        }
        cout << endl;
    }

    bool empty(){
        if (nodes_.size() == 0){
            return true;
        }
        else return false;
    }

    size_t size(){
        return nodes_.size();
    }

    void clear(){
        edges_.clear();
        nodes_.clear();
    }

    void swap(Graph<T1, T2> &obj){
        Graph<T1, T2> temp = obj;
        obj = *this;
        *this = temp;


    }

    auto cbegin() const{
        return nodes_.cbegin();
    }

    auto begin(){
        return nodes_.begin();
    }

    auto end(){
        return nodes_.end();
    }

    auto cend() const{
        return nodes_.cend();
    }

    size_t degree_in(Node<T1> A){
        size_t cnt = 0;

        for(auto i = edges_.begin(); i!= edges_.end(); i++){
            if (i->first.first.name == A.name) cnt++;
        }
        return cnt;
    }

    size_t degree_out(Node<T1> A){
        size_t cnt = 0;

        for(auto i = edges_.begin(); i!= edges_.end(); i++){
            if (i->first.second.name == A.name) cnt++;
        }
        return cnt;
    }

    bool loop(Node<T1> A){
        size_t cnt = 0;

        for(auto i = edges_.begin(); i!= edges_.end(); i++){
            if (i->first.second.name == A.name && i->first.first.name == A.name)  cnt++;
        }
        if(cnt) return true;
        else return false;
    }

    auto assign_edge(Node<T1> A, Node<T1> B, T2 W){
        bool flag = false;
        auto it = edges_.begin();
        for(auto i = edges_.begin(); i!= edges_.end(); i++){
            if (i->first.first.name == A.name && i->first.first.name == A.name){
                i->first.first.value = A.value;
                i->first.second.value = B.value;
                i->second = W;
                flag = true;
                it = i;
                break;
            }
        }
        return make_pair(it, flag);
    }

    void clear_edges(){
        edges_.clear();
    }

    bool erase_edges_go_from(Node<T1> A) {
        bool flag = false;
        auto it = edges_.begin();
        for(auto i = edges_.begin(); i!= edges_.end(); i++){
            if (i->first.first.name == A.name) {
                edges_.erase(i--);
                flag = true;
            }
        }

        return flag;
    }

    bool erase_edges_go_to(Node<T1> A) {
        bool flag = false;
        auto it = edges_.begin();
        for(auto i = edges_.begin(); i!= edges_.end(); i++){
            if (i->first.second.name == A.name) {
                edges_.erase(i--);
                flag = true;
            }
        }

        return flag;
    }

    bool erase_node(Node<T1> A){
        bool flag = false;

        erase_edges_go_from(A);
        erase_edges_go_to(A);
        for(auto i = nodes_.begin(); i != nodes_.end();i++){
            if(i ->name == A.name){
                nodes_.erase(i--);
                flag = true;
                break;
            }
        }



        return flag;
    }


    void save_to_file(string path){

        ofstream out(path);

        if(out.is_open()){
            for(auto i = edges_.begin(); i!= edges_.end(); i++){
                string name1 = i->first.first.name;
                string name2 = i->first.second.name;
                T1 val1 = i->first.first.value;
                T1 val2 = i->first.second.value;
                T2 w = i->second;

                out << name1 << ' ' << name2 << ' ' << val1 << ' ' << val2 << ' ' << w << endl;


            }
        }
        out.close();

    }


    bool load_from_file(string path){
        bool flag = false;

        ifstream in(path);
        string data;
        string del = " ";
        size_t pos = 0;
        if(in.is_open()){
            string token1;

            while(getline (in, data)){


                string name1;
                string name2;
                string val1;
                string val2;
                string w;

                pos = data.find(del);
                name1 = data.substr(0, pos);
                data.erase(0, pos + del.length());
                pos = data.find(del);


                pos = data.find(del);
                name2 = data.substr(0, pos);
                data.erase(0, pos + del.length());
                pos = data.find(del);

                pos = data.find(del);
                val1 = data.substr(0, pos);
                data.erase(0, pos + del.length());
                pos = data.find(del);

                pos = data.find(del);
                val2 = data.substr(0, pos);
                data.erase(0, pos + del.length());
                pos = data.find(del);

                pos = data.find(del);
                w = data.substr(0, pos);
                data.erase(0, pos + del.length());
                pos = data.find(del);

                Node<T1> A;
                Node<T1> B;

                A.name = name1;
                B.name = name2;
                T2 W;
                std::stringstream dstream1(val1);
                dstream1 >> A.value;
                std::stringstream dstream2(val2);
                dstream2 >> B.value;
                std::stringstream dstream(w);
                dstream >> W;


                this->makeEdge(A, B, W);



            }
            flag = true;
        }



        in.close();
        return flag;
    }

    bool load_from_matrix(string path){
        bool flag = false;

        ifstream in(path);
        string data;
        string del = " ";
        size_t pos = 0;
        if(in.is_open()) {
            string token1;
            string token2;
            vector<Node<T1>> spas;

            getline(in, data);
            while ((pos = data.find(del)) != std::string::npos) {
                token1 = data.substr(0, pos);
                data.erase(0, pos + del.length());
                pos = data.find(del);
                token2 = data.substr(0, pos);
                data.erase(0, pos + del.length());


                Node<T1> N;
                N.name = token1;
                std::stringstream dstream13(token2);
                dstream13 >> N.value;
                spas.push_back(N);

            }



            int i = 0;
            int j = 0;
//
            while (getline(in, data)) {


                T2 W;
                string w;


                while ((pos = data.find(del)) != std::string::npos) {
                    w = data.substr(0, pos);

                    std::stringstream dstream(w);
                    dstream >> W;

                    data.erase(0, pos + del.length());

                    this->makeEdge(spas[i], spas[j], W);
                    j++;
                }
                w = data.substr(0, pos);

                std::stringstream dstream(w);
                dstream >> W;
                data.erase(0, pos + del.length());
                this->makeEdge(spas[i], spas[j], W);
                j = 0;


                i++;
            }
            flag = true;


        }


        in.close();
        return flag;
    }

    bool load_from_list(string path){
        bool flag = false;

        ifstream in(path);
        string data;
        string del = " ";
        size_t pos = 0;
        if(in.is_open()) {
            string token1;
            string token2;
            vector<Node<T1>> spas;

            getline(in, data);
            while ((pos = data.find(del)) != std::string::npos) {
                token1 = data.substr(0, pos);
                data.erase(0, pos + del.length());
                pos = data.find(del);
                token2 = data.substr(0, pos);
                data.erase(0, pos + del.length());


                Node<T1> N;
                N.name = token1;
                std::stringstream dstream13(token2);
                dstream13 >> N.value;
                spas.push_back(N);

            }


            while (getline(in, data)) {


                T2 W;
                string w;
                string name;
                string name1;
                string NAME;
                string NAME1;

                NAME = data.substr(0, pos);

                std::stringstream dstream(NAME);
                dstream >> NAME1;


                data.erase(0, pos + del.length());

                //look for node wuth NAME1 name and take it's value
                int I = 0;
                for(int i = 0; i < spas.size(); i++){
                    if(spas[i].name == NAME1) I = i;
                }


                while ((pos = data.find(del)) != std::string::npos) {

                    token1 = data.substr(0, pos);

                    cout << token1 << endl;

                    int J = 0;
                    for(int i = 0; i < spas.size(); i++){
                        if(spas[i].name == token1) J = i;
                    }





                    data.erase(0, pos + del.length());

                    w = data.substr(0, pos);

                    std::stringstream dstream19(w);
                    dstream19 >> W;

                    data.erase(0, pos + del.length());

//                    cout << spas[I].name << " " << spas[J].name << endl;
                    this->makeEdge(spas[I], spas[J], W);

                }


            }
            flag = true;


        }


        in.close();
        return flag;



    }






};




template <typename T1, typename T2>
void Swap(Graph<T1, T2> &pG1, Graph<T1, T2> &pG2){
    Graph<T1, T2> temp = pG1;
    pG1 = pG2;
    pG2 = temp;
}



int main(){
    Graph<int, int> G;
    Node<int>A = {7, "A"};
    Node<int>B = {13, "B"};
    Node<int>C = {19, "C"};
    Node<int>D = {37, "D"};

    G.makeEdge(A, B, 113);
    G.makeEdge(A, C, 115);
    G.makeEdge(A, D, 1187);

    G.info_structure();
    G.info_weights_and_vertex();



//check copy construtor
    Graph<int, int> G1(G);
    G1.info_structure();
    G1.info_weights_and_vertex();

    G.info_structure();
    G.info_weights_and_vertex();


//check move construcor

    Graph<int, int> G2(move(G));
    G1.info_structure();
    G1.info_weights_and_vertex();

    G.info_structure();
    G.info_weights_and_vertex();


    //check assignment oper

    cout << endl << endl << "ASSIGNMENT" << endl;

    Graph<int, int> G3 = G2;
    G3.info_structure();
    G3.info_weights_and_vertex();



//check move assignment oper
    cout << endl << endl << "%%%% ASSIGNMENT MOVE %%%%" << endl;

    Graph<int, int> G4;
    G4 = move(G2);
    G4.info_structure();
    G4.info_weights_and_vertex();
    G2.info_structure();
    G2.info_weights_and_vertex();

    cout << "____    IS EMPTY?     ____" << endl;


    cout << "G4 empty:      " <<  boolalpha << G4.empty() << endl;
    cout << "G4 size is:     " << G4.size() << endl;
    G4.clear();
    cout << "G4 empty:      " <<  boolalpha << G4.empty() << endl;
    cout << "G4 size is:     " << G4.size() << endl;


    Graph<int, int> G5;
    Graph<int, int> G6;

    G5.makeEdge(A, B, 123);
    G6.makeEdge(D, C, 1999);

    G5.info_structure();
    G6.info_structure();

    //G5.swap(G6);
    Swap(G5, G6);

    G5.info_structure();
    G6.info_structure();

    G5.swap(G6);

    cout << endl << endl << endl;
    G5.info_structure();
    G6.info_structure();

    //degree_in
    cout << "   %%%%    FUNTCIONS BY KEY     %%%%    " << endl << endl;
    G6.makeEdge(A,B, 5656);
    G6.makeEdge(A,B, 9898989);
    cout <<"degree of A in G6: " << G6.degree_in(A) << endl;



    cout <<"assign edge in G5: " <<  G5.assign_edge(A, B, 993).second << endl;

    cout << endl << endl << "   %%%%    ERASING     %%%%    " << endl << endl;

    //delete A-containing edges
    G5.makeEdge(B, A, 1);
    G5.makeEdge(A, C, 2);
    G5.makeEdge(A, D, 3);
    G5.makeEdge(C, A, 4);
    G5.info_weights_and_vertex();

    G5.erase_edges_go_from(A);

    G5.info_weights_and_vertex();

    G5.erase_edges_go_to(A);

    G5.info_weights_and_vertex();


    G5.makeEdge(B, D, 0);
    G5.makeEdge(B, A, 1);
    G5.makeEdge(A, C, 2);
    G5.makeEdge(A, D, 3);
    G5.makeEdge(C, A, 4);

    G5.erase_node(A);

    G5.info_structure();
    //saving and loading
    cout << "     %%%% SAVE TO FILE %%%%      " << endl;


    G5.makeEdge(B, A, 1);
    G5.makeEdge(A, C, 2);
    G5.makeEdge(A, D, 3);
    G5.makeEdge(C, A, 4);

    G5.save_to_file("test.txt");

    Graph<int, int> G8;
    G8.load_from_file("C:/Users/msmkl/CLionProjects/untitled2/cmake-build-debug/test.txt");
    cout << "       ____G8____        " << endl;
    G8.info_weights_and_vertex();

    Graph<int, int> G9;
    G9.load_from_matrix("C:/Users/msmkl/CLionProjects/untitled2/cmake-build-debug/testm.txt");
    G9.info_weights_and_vertex();

//    Graph<int, int> G10;
//    G10.load_from_list("C:/Users/msmkl/CLionProjects/untitled2/cmake-build-debug/testL.txt");
//    G10.info_weights_and_vertex();

}