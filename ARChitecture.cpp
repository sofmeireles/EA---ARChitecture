#include <vector>
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

int h, n, H;

int mod_abs(int a, int mod){
    return ((a % mod) + mod) % mod;
}

int mod_add(int a, int b, int mod){
    return (mod_abs(a, mod) + mod_abs(b, mod)) % mod;
}

int mod_sub(int a, int b, int mod){
    return mod_add(a, -b, mod);
}

void print_adj(vector<vector<vector<int>>> &v){
    printf("adj[0].size() = %d  adj.size() = %d\n",(int)v[0].size(),(int)v.size());
    for(int i = 0; i<(int)v.size(); i++){
        for(int j = 0;j<(int)v[0].size();j++){
            printf("[%d,%d] ",v[i][j][0],v[i][j][1]);
        }
        printf("\n");
    }
}
void print_adjs(vector<vector<vector<int>>> &v,vector<vector<vector<int>>> &v2){
    for(int i = 0; i<(int)v.size(); i++){
        for(int j = 0;j<(int)v[0].size();j++){
            printf("[%d,%d]  [%d,%d]",v[i][j][0],v[i][j][1],v2[i][j][0],v2[i][j][1]);
        }
        printf("\n");
    }
}
int arc(vector<vector<vector<int>>> &adj){

    int aux = 0;
    int sobe = 0;
    int desce = 0;
    int conta=0;
    for(int col = 0;col<n;col++){
        sobe=0;
        desce=0;
        for(int i = 1; i < h && col!=0 && i<H-h+1;i++){
            desce=mod_add(desce,adj[i][0][0],1000000007);
            desce=mod_add(desce,adj[i][0][1],1000000007);
            
        }

        vector<vector<vector<int>>> adj2 = vector<vector<vector<int>>>(H-h+1, vector<vector<int>>(1, vector<int>(2, 0)));

        for(int line = 0; line<=H-h && line <= aux;line++){
         
            if(line==1 && col==n-1){
                break;
            }

            if(line==0){
                conta = mod_add(conta,adj[line][0][1], 1000000007);
                adj2[line][0][1]=desce;
                
            }

            if(line!=0){
                if(line>h-1 && col>0){
                    sobe=mod_sub(sobe,adj[line-h][0][0],1000000007);
                }
                sobe=mod_add(sobe,adj[line-1][0][0],1000000007);
                
                adj2[line][0][0]=sobe;

                if(line<=H-h-h+1 && col>1){
                    desce=mod_add(desce,adj[line+h-1][0][0],1000000007);
                    desce=mod_add(desce,adj[line+h-1][0][1],1000000007);
                }
                desce=mod_sub(desce,adj[line][0][0],1000000007);
                desce=mod_sub(desce,adj[line][0][1],1000000007);
                
                adj2[line][0][1]=desce;
            }
        }
        if (col > (n/2.0)-1){
            aux -= h - 1;
        }else if (col-2 < (n/2.0)){
            aux += h - 1;
        }
    
        if(col!=0){
            adj=adj2;
        }
    }
    conta = mod_add(conta,adj[0][0][1], 1000000007);
    return conta;
}

int main(){

    std::ios_base::sync_with_stdio(0);
    std::cin.tie(0);

    int n_testes, conta;
    cin >> n_testes;

    for (int i = 0; i < n_testes; i++){
        cin >> n >> h >> H;
        vector<vector<vector<int>>> adj = vector<vector<vector<int>>>(H-h+1, vector<vector<int>>(1, vector<int>(2, 0)));
        adj[0][0][0]=1;
        adj[0][0][1]=0;
        conta = arc(adj);
        cout << mod_abs(conta, 1000000007) << "\n";
       // print_adj(adj);
       // print_matriz(v);
    }
}