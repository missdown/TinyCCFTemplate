//
// Created by miss on 19-1-21.
//

#ifndef ACM_TEMPLATE_UFSET_H
#define ACM_TEMPLATE_UFSET_H

namespace UFSet {
    /*
     * UNION FIND SET
     */
    int father[N];

    void Init() {
        for (int i = 1; i <= N; i++) {
            father[i] = i;
        }
    }

    /*
     * FIND
     */
    int findFather(int x) {
        while(x != father[x]) {
            x = father[x];
        }
        return x;
    }

    int findFather2(int x) {
        if(x == father[x]) return x;
        else return findFather2(father[x]);
    }

    // FASTER METHOD BELOW
    int findFather3(int x){
        int a = x;
        while(x != father[x])   //FINDING ROOT
            x = father[x];
        while(a != father[a]) {
            int temp = a;    // set father a = Root
            a = father[a];
            father[temp] = x;
        }
        return x;
    }

    /*
     * UNION
     */
    void Union(int a, int b) {
        int faA = findFather(a);
        int faB = findFather(b);
        if(faA != faB)
            father[faA] = faB;
    }


}

#endif //ACM_TEMPLATE_UFSET_H
