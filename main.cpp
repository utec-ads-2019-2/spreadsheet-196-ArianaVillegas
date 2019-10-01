#include <iostream>

using namespace std;

class Sheet{
    int c,f;
    int** solutions;
    bool** pro;
    string** cells;
public:
    Sheet(int c, int f):c(c),f(f){
        cells = new string*[f];
        solutions = new int*[f];
        pro = new bool*[f];
        string* cn = new string[f*c];
        int* sn = new int[f*c];
        bool* bn = new bool[f*c];
        for(int i=0;i<f; ++i){
            cells[i]=&cn[c*i];
            solutions[i]=&sn[c*i];
            pro[i]=&bn[c*i];
        }
    };
    void fillSheet(){
        string cell;
        for(int i=0;i<f;++i){
            for(int j=0;j<c;++j){
                cin>>cell;
                cells[i][j]=cell;
                pro[i][j]=0;
            }
        }
    }
    int parseCell(string cell){
        int f=0,c=0,sol;
        int size=cell.size();
        for(int i=0;i<size;++i){
            if(cell[i]>=65 && cell[i]<=90){
                c*=26;
                c+=(cell[i]-64);
            }else{
                f=stoi(cell.substr(i,size-i));
                break;
            }
        }
        --f;--c;
        if(cells[f][c][0]=='='){
            sol=executeCell(cells[f][c].substr(1,cells[f][c].size()-1));
        } else {
            sol=stoi(cells[f][c]);
        }
        solutions[f][c]=sol;
        pro[f][c]=1;
        return sol;
    }
    int executeCell(string formula){
        string cell;
        int res=0;
        for(int i=0;i<formula.size();++i){
            if(formula[i]!='+'){
                cell+=formula[i];
            }else{
                res+=parseCell(cell);
                cell.clear();
            }
        }
        res+=parseCell(cell);
        return res;
    }
    void solveSheet(){
        for(int i=0;i<f;++i){
            for(int j=0;j<c;++j){
                if(!pro[i][j]) {
                    if (cells[i][j][0] == '=') {
                        solutions[i][j] = executeCell(cells[i][j].substr(1, cells[i][j].size() - 1));
                    } else {
                        solutions[i][j] = stoi(cells[i][j]);
                    }
                    pro[i][j]=1;
                }
            }
        }
    }
    void printSheet(){
        for(int i=0;i<f;++i){
            for(int j=0;j<c;++j){
                if(j) cout << ' ';
                cout << solutions[i][j];
            }
            cout << '\n';
        }
    }
};

int main() {
    int cases,c,f;
    cin>>cases;
    for(int i=0;i<cases;++i){
        cin>>c>>f;
        Sheet st(c,f);
        st.fillSheet();
        st.solveSheet();
        st.printSheet();
    }
    return 0;
}