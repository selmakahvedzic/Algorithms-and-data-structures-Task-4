#include <iostream>
#include<string>

using namespace std; 

template<typename TipKljuca, typename TipVrijednosti>
class Mapa{
   public: 
    Mapa(){}
    virtual ~Mapa(){}
    virtual int brojElemenata() const{return 0; }
    virtual TipVrijednosti &operator[](TipKljuca kljuc)=0; 
    virtual TipVrijednosti operator[](TipKljuca kljuc)const=0; 
    virtual void obrisi(){}
    virtual void obrisi(const TipKljuca &kljuc) {}
        
    }; 
    
    
//Binarni cvor

template <typename TipKljuca, typename TipVrijednosti>
struct BCvor {
    TipKljuca kljuc;
    TipVrijednosti vrijednost;
    BCvor<TipKljuca,TipVrijednosti>* roditelj=nullptr;
    BCvor<TipKljuca,TipVrijednosti>* lijevi=nullptr;
    BCvor<TipKljuca,TipVrijednosti>* desni=nullptr;
};

//klasa BinStabloMapa

template <typename TipKljuca, typename TipVrijednosti>
class BinStabloMapa : public Mapa<TipKljuca,TipVrijednosti> {
    private:
    BCvor<TipKljuca,TipVrijednosti>* korijen;
    int broj;
    void preorderKopiraj(BCvor<TipKljuca,TipVrijednosti>* cvor1, BCvor<TipKljuca,TipVrijednosti>* &cvor2, BCvor<TipKljuca,TipVrijednosti>* prethodni=nullptr); 
    public:
    BinStabloMapa() : korijen(nullptr), broj(0) {}
    ~BinStabloMapa() { this-> obrisi(); }
    BinStabloMapa(const BinStabloMapa &bsm);
    BinStabloMapa(BinStabloMapa &&bsm) : korijen(bsm.korijen), broj(bsm.broj) {}
    BinStabloMapa &operator=(const BinStabloMapa &bsm);
    BinStabloMapa &operator=(BinStabloMapa &&bsm);
    int brojElemenata() const { return broj; }
    TipVrijednosti &operator[] (TipKljuca kljuc);
    TipVrijednosti operator [] (TipKljuca kljuc) const;
    void obrisi();
    void obrisi(const TipKljuca &kljuc);
    };
    
    template <typename TipKljuca, typename TipVrijednosti>
    BinStabloMapa<TipKljuca,TipVrijednosti> &BinStabloMapa<TipKljuca,TipVrijednosti>::operator=(  BinStabloMapa &&bsm) {
    //samododjela 
    if(this==&bsm) return *this;
    //brisanje
    this->obrisi();
    //kopiranje
    korijen=bsm.korijen;
    broj=bsm.broj;
    return *this;
    }

    template <typename TipKljuca, typename TipVrijednosti>
        BinStabloMapa<TipKljuca,TipVrijednosti> &BinStabloMapa<TipKljuca,TipVrijednosti>::operator=(const BinStabloMapa &bsm) {
            //samododjela
            if(this==&bsm) return *this;
            //brisanje
            this->obrisi();
            //kopiranje
            preorderKopiraj(bsm.korijen,korijen);
            broj=bsm.broj;
            return *this;
     }
     
     template <typename TipKljuca, typename TipVrijednosti>
     void BinStabloMapa<TipKljuca,TipVrijednosti>::preorderKopiraj(BCvor<TipKljuca, TipVrijednosti>* cvor1, BCvor<TipKljuca,TipVrijednosti>* &cvor2, BCvor<TipKljuca,TipVrijednosti>* prethodni) {
         if(cvor1!=nullptr) {
             cvor2=new BCvor<TipKljuca,TipVrijednosti>();
             cvor2->kljuc=cvor1->kljuc;
             cvor2->vrijednost=cvor1->vrijednost;
             cvor2->roditelj=prethodni;
             preorderKopiraj(cvor1->lijevi, cvor2->lijevi, cvor2);
             preorderKopiraj(cvor1->desni, cvor2->desni, cvor2);
         }
     }
     
     template <typename TipKljuca, typename TipVrijednosti>
     BinStabloMapa<TipKljuca,TipVrijednosti>::BinStabloMapa(const BinStabloMapa &bsm) :broj(bsm.broj) {
         preorderKopiraj(bsm.korijen, korijen);
     }
     
     template <typename TipKljuca, typename TipVrijednosti>
     void BinStabloMapa<TipKljuca,TipVrijednosti>::obrisi(const TipKljuca &kljuc) {
         BCvor<TipKljuca,TipVrijednosti>* p=korijen, *roditelj=nullptr;
         while (p!=nullptr && kljuc!=p->kljuc) {
             roditelj=p;
             if (kljuc<p->kljuc) p=p->lijevi;
             else p=p->desni;
         }
                 if(p==nullptr) return;
                 BCvor<TipKljuca,TipVrijednosti>* m;
                 if(p->lijevi==nullptr) m=p->desni;
                 else {
                     if(p->desni==nullptr) m=p->lijevi;
                     else {
                         BCvor<TipKljuca,TipVrijednosti>* pm=p, *tmp;
                         m=p->lijevi;
                         tmp=m->desni;
                         while (tmp!=nullptr) {
                             pm=m;
                             m=tmp;
                             tmp=m->desni;
                             
                     }
                     if(pm!=p) {
                         pm->desni=m->lijevi;
                         m->lijevi=p->lijevi;
                         
                     }
                     m->desni=p->desni;
                     }
                 }
                 if(roditelj==nullptr) korijen=m;
                 else {
                     if(p==roditelj->lijevi) roditelj->lijevi=m;
                     else roditelj->desni=m;
                
                 }
                 delete p;
                 broj--;
             
         }
             
             template <typename TipKljuca, typename TipVrijednosti>
             void BinStabloMapa<TipKljuca,TipVrijednosti>::obrisi() {
                 while (korijen!=nullptr) obrisi(korijen->kljuc);
             }
             
             template <typename TipKljuca, typename TipVrijednosti>
             TipVrijednosti BinStabloMapa<TipKljuca,TipVrijednosti>::operator[] (TipKljuca kljuc) const {
                 //pretraga
                 BCvor<TipKljuca,TipVrijednosti>* temp=korijen;
                 while(temp!=nullptr && kljuc!=temp->kljuc) {
                     if(kljuc<temp->kljuc) temp=temp->lijevi;
                     else temp=temp->desni;
                }
                //nije pronaslo
                if(temp==nullptr) return TipVrijednosti();
                //pronaslo
                return temp->vrijednost;
             }
             
             template <typename TipKljuca, typename TipVrijednosti>
             TipVrijednosti &BinStabloMapa<TipKljuca,TipVrijednosti>::operator[] (TipKljuca kljuc) {
                 //pretraga
                 BCvor<TipKljuca,TipVrijednosti>* temp=korijen;
                 while (temp!=nullptr && kljuc!=temp->kljuc) {
                     if(kljuc<temp->kljuc) temp=temp->lijevi;
                     else temp=temp->desni;
                }
                //nije pronaslo, dodavanje
               if(temp==nullptr)  {
                    temp=new BCvor<TipKljuca,TipVrijednosti>();
                    broj++;
                    temp->kljuc=kljuc;
                    temp->vrijednost=TipVrijednosti();
                    BCvor<TipKljuca,TipVrijednosti>* x=korijen,*y=nullptr;
                    while (x!=nullptr) {
                        y=x;
                        if(temp->kljuc<x->kljuc) x=x->lijevi;
                        else x=x->desni;
                    }
                    if(y==nullptr) korijen=temp;
                    else {
                        if(temp->kljuc<y->kljuc) y->lijevi=temp;
                        else y->desni=temp;
                        temp->roditelj=y;
                    }
               }
               return temp->vrijednost;
        }
        
        
        //AVL Cvor
        
        template <typename TipKljuca, typename TipVrijednosti>
        struct AVLCvor {
            TipKljuca kljuc;
            TipVrijednosti vrijednost;
            AVLCvor<TipKljuca,TipVrijednosti>* roditelj=nullptr;
            AVLCvor<TipKljuca,TipVrijednosti>* lijevi=nullptr;
            AVLCvor<TipKljuca,TipVrijednosti>* desni=nullptr;
            int balans=0;
        };
        
        
        //klasa AVLStabloMapa
        
        template <typename TipKljuca, typename TipVrijednosti>
        class AVLStabloMapa : public Mapa<TipKljuca,TipVrijednosti> {
            private:
            AVLCvor<TipKljuca,TipVrijednosti>* korijen;
            int broj;
            void ubaci(AVLCvor<TipKljuca,TipVrijednosti>* cvor);
            void preorderKopiraj(AVLCvor<TipKljuca,TipVrijednosti>* cvor1, AVLCvor<TipKljuca,TipVrijednosti>* &cvor2, AVLCvor<TipKljuca,TipVrijednosti>* prethodni=nullptr);
            void azurirajBalans(AVLCvor<TipKljuca,TipVrijednosti>* cvor);
            void lijevaRotacija(AVLCvor<TipKljuca,TipVrijednosti>* cvor);
            void desnaRotacija(AVLCvor<TipKljuca,TipVrijednosti>* cvor);
            void brisi(AVLCvor<TipKljuca,TipVrijednosti>* covr);
            public:
               AVLStabloMapa() : korijen(nullptr), broj(0) {}
               ~AVLStabloMapa() { this->obrisi(); }
               AVLStabloMapa(const AVLStabloMapa &avl);
               AVLStabloMapa(AVLStabloMapa &&avl) : korijen(avl.korijen), broj(avl.broj) {}
               AVLStabloMapa &operator=(const AVLStabloMapa &avl);
               AVLStabloMapa &operator=(AVLStabloMapa &&avl);
               int brojElemenata() const { return broj; }
               TipVrijednosti &operator [] (TipKljuca kljuc);
               TipVrijednosti operator [] (TipKljuca kljuc) const;
               void obrisi() { brisi(korijen); korijen=nullptr; broj=0; }
               void obrisi(const TipKljuca &kljuc);
        };
        
        template <typename TipKljuca, typename TipVrijednosti>
        void AVLStabloMapa<TipKljuca,TipVrijednosti>::brisi(AVLCvor<TipKljuca,TipVrijednosti>* covr)  {
            if(covr!=nullptr)  {
                brisi(covr->lijevi);
                brisi(covr->desni);
                delete covr;
            }
        }
        
        template <typename TipKljuca, typename TipVrijednosti>
        void AVLStabloMapa<TipKljuca,TipVrijednosti>::obrisi(const TipKljuca &kljuc) {
            AVLCvor<TipKljuca,TipVrijednosti>* p=korijen, *roditelj=nullptr;
            while (p!=nullptr && kljuc!=p->kljuc) {
                roditelj=p;
                if (kljuc<p->kljuc) p=p->lijevi;
                else p=p->desni;
          }
          if (p==nullptr) return;
          AVLCvor<TipKljuca,TipVrijednosti>* m;
          if (p->lijevi==nullptr) m=p->desni;
          else {
              if (p->desni==nullptr) m=p->lijevi;
              else {
                  AVLCvor<TipKljuca,TipVrijednosti>* pm=p, *tmp;
                  m=p->lijevi;
                  tmp=m->desni;
                  while (tmp!=nullptr) {
                      pm=m;
                      m=tmp;
                      tmp=m->desni;
                 }
                 if(pm!=p) {
                     pm->desni=m->lijevi;
                     m->lijevi=p->lijevi;
                }
                m->desni=p->desni;
            }
         }
         if (roditelj==nullptr) korijen=m;
         else {
             if(p==roditelj->lijevi) roditelj->lijevi=m,roditelj->balans--;
             else roditelj->desni=m,roditelj->balans++;
        }
        delete p;
        p=nullptr;
        broj--;
    }
    
    
    template<typename TipKljuca, typename TipVrijednosti>
    void AVLStabloMapa <TipKljuca, TipVrijednosti>:: ubaci(AVLCvor<TipKljuca, TipVrijednosti>* cvor){
        AVLCvor<TipKljuca, TipVrijednosti>* p= cvor->roditelj; 
        TipKljuca kljuc= cvor->kljuc; 
        if(p==nullptr) {
            korijen=cvor; 
            broj++; 
            return; 
        }
        if(p!=nullptr && (p->lijevi!=nullptr && p->desni!=nullptr)){
            if(kljuc<p->kljuc) p=p->lijevi; 
            else p=p->desni; 
            if(kljuc<p->kljuc) p->lijevi=cvor; 
            else p->desni=cvor; 
            azurirajBalans(cvor); 
            broj++; 
            return; 
        }
        else if(p!=nullptr){
            p->balans=0; 
            if(kljuc<p->kljuc) p->lijevi=cvor; 
            else p->desni=cvor; 
            broj++; 
            return; 
        }
    }
          
  template<typename TipKljuca, typename TipVrijednosti>
  void AVLStabloMapa<TipKljuca, TipVrijednosti>:: lijevaRotacija(AVLCvor<TipKljuca, TipVrijednosti>*cvor)
 {
     if(cvor->balans* cvor->desni->balans <0)
         desnaRotacija(cvor->desni); 
    AVLCvor<TipKljuca, TipVrijednosti>* temp= cvor->desni; 
    temp->roditelj= cvor->roditelj; 
    cvor->desni= nullptr; 
    temp->lijevi= cvor; 
    cvor->roditelj= temp; 
    temp->balans=0; 
    cvor->balans=0; 
    
 }
 
 template<typename TipKljuca, typename TipVrijednosti>
 void AVLStabloMapa<TipKljuca, TipVrijednosti>::desnaRotacija(AVLCvor<TipKljuca, TipVrijednosti>*cvor){
     if( cvor->balans*cvor->lijevi->balans<0)
        lijevaRotacija(cvor->lijevi); 
        AVLCvor<TipKljuca, TipVrijednosti>* temp= cvor->lijevi; 
        temp->roditelj= cvor->roditelj; 
        cvor->lijevi=nullptr; 
        temp->desni= cvor; 
        cvor->roditelj= temp; 
        temp->balans=0; 
        cvor->balans=0; 
 }

template<typename TipKljuca, typename TipVrijednosti>
void AVLStabloMapa<TipKljuca, TipVrijednosti>:: azurirajBalans(AVLCvor<TipKljuca, TipVrijednosti>* cvor){
   if(cvor== korijen) return; 
   AVLCvor<TipKljuca, TipVrijednosti> *p= cvor->roditelj; 
   if(p->lijevi== cvor) p->balans++; 
   else p->balans--; 
   if(p->balans>1) desnaRotacija(p); 
   else if(p->balans<-1) lijevaRotacija(p); 
   azurirajBalans(p); 
}

template<typename TipKljuca, typename TipVrijednosti>
AVLStabloMapa<TipKljuca, TipVrijednosti> & AVLStabloMapa<TipKljuca, TipVrijednosti>:: operator =(AVLStabloMapa && avl){
    if(this== & avl) return * this; 
    this->obrisi(); 
    korijen= avl.korijen; 
    broj=avl.broj; 
    return * this; 
}

template<typename TipKljuca, typename TipVrijednosti>
AVLStabloMapa<TipKljuca, TipVrijednosti> &AVLStabloMapa<TipKljuca, TipVrijednosti> :: operator =(const AVLStabloMapa & avl){
    if(this== & avl) return *this; 
    this->obrisi(); 
    preorderKopiraj(avl.korijen, korijen); 
    broj=avl.broj; 
    return *this; 
}

template<typename TipKljuca, typename TipVrijednosti>
void AVLStabloMapa<TipKljuca, TipVrijednosti>:: preorderKopiraj(AVLCvor<TipKljuca, TipVrijednosti>* cvor1, AVLCvor<TipKljuca, TipVrijednosti>* &cvor2, AVLCvor<TipKljuca, TipVrijednosti>* prethodni){
    if(cvor1!=nullptr){
        cvor2= new AVLCvor<TipKljuca, TipVrijednosti>(); 
        cvor2->kljuc= cvor1->kljuc; 
        cvor2->vrijednost= cvor1->vrijednost; 
        cvor2->roditelj= prethodni; 
        preorderKopiraj(cvor1->lijevi, cvor2->lijevi, cvor2); 
        preorderKopiraj(cvor1->desni, cvor2->desni, cvor2); 
        
    }
}

template<typename TipKljuca, typename TipVrijednosti>
AVLStabloMapa<TipKljuca, TipVrijednosti>:: AVLStabloMapa(const AVLStabloMapa & bsm): broj(bsm.broj){
    preorderKopiraj(bsm.korijen, korijen); 
}
 

template<typename TipKljuca, typename TipVrijednosti>
TipVrijednosti AVLStabloMapa<TipKljuca, TipVrijednosti>::operator [] (TipKljuca kljuc) const{
    AVLCvor<TipKljuca, TipVrijednosti> * temp= korijen; 
    while (temp!=nullptr && temp->kljuc != kljuc) {
        if(kljuc<temp->kljuc) temp=temp->lijevi; 
        else temp=temp->desni; 
    }

    if(temp==nullptr ) return TipVrijednosti(); 
    return temp->vrijednost; 
}

template<typename TipKljuca, typename TipVrijednosti>
TipVrijednosti & AVLStabloMapa<TipKljuca, TipVrijednosti>:: operator [](TipKljuca kljuc){
    AVLCvor<TipKljuca, TipVrijednosti>* p= korijen, *temp=korijen; 
    while (temp!=nullptr && temp->kljuc != kljuc) {
        p= temp; 
        if(kljuc<temp->kljuc) temp=temp->lijevi; 
        else temp=temp->desni; 
        
    }

   if(temp==nullptr){
        AVLCvor<TipKljuca, TipVrijednosti>* cvor= new AVLCvor<TipKljuca, TipVrijednosti>(); 
        cvor->kljuc=kljuc; 
        cvor->vrijednost= TipVrijednosti(); 
        cvor->lijevi=nullptr; 
        cvor->desni=nullptr; 
         cvor->roditelj=p; 
        cvor->balans=0; 
        ubaci(cvor); 
        return cvor->vrijednost; 
        
   }
    return temp->vrijednost; 
}

int main() {
 
    
    
    AVLStabloMapa<int, int> avl; 
    BinStabloMapa<int, int>bsm; 
    clock_t t1=clock(); 
    for(int i=0; i<7500; i++) bsm[i]= i; 
    clock_t t2= clock(); 
    clock_t t3= clock(); 
    for(int i=0; i<7500; i++) avl[i]= i; 
    clock_t t4= clock();  
    cout<<"Vrijeme unosa 7500 elemenata za binarno stablo je "<< (t2-t1)/(CLOCKS_PER_SEC/1000)<<"a za AVL stablo "<< (t4-t3)/(CLOCKS_PER_SEC/1000); 
    
    
    t1= clock(); 
    for(int i=0; i<7500; i++) bsm.obrisi(i); 
    t2=clock(); 
    t3=clock(); 
    for(int i=0; i<7500; i++) avl.obrisi(i); 
    t4=clock(); 
    cout<<(t2-t1)/(CLOCKS_PER_SEC/1000)<<(t4-t3)/(CLOCKS_PER_SEC/1000); 
    
    
    return 0;
}#include <iostream>
#include<string>

using namespace std; 

template<typename TipKljuca, typename TipVrijednosti>
class Mapa{
   public: 
    Mapa(){}
    virtual ~Mapa(){}
    virtual int brojElemenata() const{return 0; }
    virtual TipVrijednosti &operator[](TipKljuca kljuc)=0; 
    virtual TipVrijednosti operator[](TipKljuca kljuc)const=0; 
    virtual void obrisi(){}
    virtual void obrisi(const TipKljuca &kljuc) {}
        
    }; 
    
    
//Binarni cvor

template <typename TipKljuca, typename TipVrijednosti>
struct BCvor {
    TipKljuca kljuc;
    TipVrijednosti vrijednost;
    BCvor<TipKljuca,TipVrijednosti>* roditelj=nullptr;
    BCvor<TipKljuca,TipVrijednosti>* lijevi=nullptr;
    BCvor<TipKljuca,TipVrijednosti>* desni=nullptr;
};

//klasa BinStabloMapa

template <typename TipKljuca, typename TipVrijednosti>
class BinStabloMapa : public Mapa<TipKljuca,TipVrijednosti> {
    private:
    BCvor<TipKljuca,TipVrijednosti>* korijen;
    int broj;
    void preorderKopiraj(BCvor<TipKljuca,TipVrijednosti>* cvor1, BCvor<TipKljuca,TipVrijednosti>* &cvor2, BCvor<TipKljuca,TipVrijednosti>* prethodni=nullptr); 
    public:
    BinStabloMapa() : korijen(nullptr), broj(0) {}
    ~BinStabloMapa() { this-> obrisi(); }
    BinStabloMapa(const BinStabloMapa &bsm);
    BinStabloMapa(BinStabloMapa &&bsm) : korijen(bsm.korijen), broj(bsm.broj) {}
    BinStabloMapa &operator=(const BinStabloMapa &bsm);
    BinStabloMapa &operator=(BinStabloMapa &&bsm);
    int brojElemenata() const { return broj; }
    TipVrijednosti &operator[] (TipKljuca kljuc);
    TipVrijednosti operator [] (TipKljuca kljuc) const;
    void obrisi();
    void obrisi(const TipKljuca &kljuc);
    };
    
    template <typename TipKljuca, typename TipVrijednosti>
    BinStabloMapa<TipKljuca,TipVrijednosti> &BinStabloMapa<TipKljuca,TipVrijednosti>::operator=(  BinStabloMapa &&bsm) {
    //samododjela 
    if(this==&bsm) return *this;
    //brisanje
    this->obrisi();
    //kopiranje
    korijen=bsm.korijen;
    broj=bsm.broj;
    return *this;
    }

    template <typename TipKljuca, typename TipVrijednosti>
        BinStabloMapa<TipKljuca,TipVrijednosti> &BinStabloMapa<TipKljuca,TipVrijednosti>::operator=(const BinStabloMapa &bsm) {
            //samododjela
            if(this==&bsm) return *this;
            //brisanje
            this->obrisi();
            //kopiranje
            preorderKopiraj(bsm.korijen,korijen);
            broj=bsm.broj;
            return *this;
     }
     
     template <typename TipKljuca, typename TipVrijednosti>
     void BinStabloMapa<TipKljuca,TipVrijednosti>::preorderKopiraj(BCvor<TipKljuca, TipVrijednosti>* cvor1, BCvor<TipKljuca,TipVrijednosti>* &cvor2, BCvor<TipKljuca,TipVrijednosti>* prethodni) {
         if(cvor1!=nullptr) {
             cvor2=new BCvor<TipKljuca,TipVrijednosti>();
             cvor2->kljuc=cvor1->kljuc;
             cvor2->vrijednost=cvor1->vrijednost;
             cvor2->roditelj=prethodni;
             preorderKopiraj(cvor1->lijevi, cvor2->lijevi, cvor2);
             preorderKopiraj(cvor1->desni, cvor2->desni, cvor2);
         }
     }
     
     template <typename TipKljuca, typename TipVrijednosti>
     BinStabloMapa<TipKljuca,TipVrijednosti>::BinStabloMapa(const BinStabloMapa &bsm) :broj(bsm.broj) {
         preorderKopiraj(bsm.korijen, korijen);
     }
     
     template <typename TipKljuca, typename TipVrijednosti>
     void BinStabloMapa<TipKljuca,TipVrijednosti>::obrisi(const TipKljuca &kljuc) {
         BCvor<TipKljuca,TipVrijednosti>* p=korijen, *roditelj=nullptr;
         while (p!=nullptr && kljuc!=p->kljuc) {
             roditelj=p;
             if (kljuc<p->kljuc) p=p->lijevi;
             else p=p->desni;
         }
                 if(p==nullptr) return;
                 BCvor<TipKljuca,TipVrijednosti>* m;
                 if(p->lijevi==nullptr) m=p->desni;
                 else {
                     if(p->desni==nullptr) m=p->lijevi;
                     else {
                         BCvor<TipKljuca,TipVrijednosti>* pm=p, *tmp;
                         m=p->lijevi;
                         tmp=m->desni;
                         while (tmp!=nullptr) {
                             pm=m;
                             m=tmp;
                             tmp=m->desni;
                             
                     }
                     if(pm!=p) {
                         pm->desni=m->lijevi;
                         m->lijevi=p->lijevi;
                         
                     }
                     m->desni=p->desni;
                     }
                 }
                 if(roditelj==nullptr) korijen=m;
                 else {
                     if(p==roditelj->lijevi) roditelj->lijevi=m;
                     else roditelj->desni=m;
                
                 }
                 delete p;
                 broj--;
             
         }
             
             template <typename TipKljuca, typename TipVrijednosti>
             void BinStabloMapa<TipKljuca,TipVrijednosti>::obrisi() {
                 while (korijen!=nullptr) obrisi(korijen->kljuc);
             }
             
             template <typename TipKljuca, typename TipVrijednosti>
             TipVrijednosti BinStabloMapa<TipKljuca,TipVrijednosti>::operator[] (TipKljuca kljuc) const {
                 //pretraga
                 BCvor<TipKljuca,TipVrijednosti>* temp=korijen;
                 while(temp!=nullptr && kljuc!=temp->kljuc) {
                     if(kljuc<temp->kljuc) temp=temp->lijevi;
                     else temp=temp->desni;
                }
                //nije pronaslo
                if(temp==nullptr) return TipVrijednosti();
                //pronaslo
                return temp->vrijednost;
             }
             
             template <typename TipKljuca, typename TipVrijednosti>
             TipVrijednosti &BinStabloMapa<TipKljuca,TipVrijednosti>::operator[] (TipKljuca kljuc) {
                 //pretraga
                 BCvor<TipKljuca,TipVrijednosti>* temp=korijen;
                 while (temp!=nullptr && kljuc!=temp->kljuc) {
                     if(kljuc<temp->kljuc) temp=temp->lijevi;
                     else temp=temp->desni;
                }
                //nije pronaslo, dodavanje
               if(temp==nullptr)  {
                    temp=new BCvor<TipKljuca,TipVrijednosti>();
                    broj++;
                    temp->kljuc=kljuc;
                    temp->vrijednost=TipVrijednosti();
                    BCvor<TipKljuca,TipVrijednosti>* x=korijen,*y=nullptr;
                    while (x!=nullptr) {
                        y=x;
                        if(temp->kljuc<x->kljuc) x=x->lijevi;
                        else x=x->desni;
                    }
                    if(y==nullptr) korijen=temp;
                    else {
                        if(temp->kljuc<y->kljuc) y->lijevi=temp;
                        else y->desni=temp;
                        temp->roditelj=y;
                    }
               }
               return temp->vrijednost;
        }
        
        
        //AVL Cvor
        
        template <typename TipKljuca, typename TipVrijednosti>
        struct AVLCvor {
            TipKljuca kljuc;
            TipVrijednosti vrijednost;
            AVLCvor<TipKljuca,TipVrijednosti>* roditelj=nullptr;
            AVLCvor<TipKljuca,TipVrijednosti>* lijevi=nullptr;
            AVLCvor<TipKljuca,TipVrijednosti>* desni=nullptr;
            int balans=0;
        };
        
        
        //klasa AVLStabloMapa
        
        template <typename TipKljuca, typename TipVrijednosti>
        class AVLStabloMapa : public Mapa<TipKljuca,TipVrijednosti> {
            private:
            AVLCvor<TipKljuca,TipVrijednosti>* korijen;
            int broj;
            void ubaci(AVLCvor<TipKljuca,TipVrijednosti>* cvor);
            void preorderKopiraj(AVLCvor<TipKljuca,TipVrijednosti>* cvor1, AVLCvor<TipKljuca,TipVrijednosti>* &cvor2, AVLCvor<TipKljuca,TipVrijednosti>* prethodni=nullptr);
            void azurirajBalans(AVLCvor<TipKljuca,TipVrijednosti>* cvor);
            void lijevaRotacija(AVLCvor<TipKljuca,TipVrijednosti>* cvor);
            void desnaRotacija(AVLCvor<TipKljuca,TipVrijednosti>* cvor);
            void brisi(AVLCvor<TipKljuca,TipVrijednosti>* covr);
            public:
               AVLStabloMapa() : korijen(nullptr), broj(0) {}
               ~AVLStabloMapa() { this->obrisi(); }
               AVLStabloMapa(const AVLStabloMapa &avl);
               AVLStabloMapa(AVLStabloMapa &&avl) : korijen(avl.korijen), broj(avl.broj) {}
               AVLStabloMapa &operator=(const AVLStabloMapa &avl);
               AVLStabloMapa &operator=(AVLStabloMapa &&avl);
               int brojElemenata() const { return broj; }
               TipVrijednosti &operator [] (TipKljuca kljuc);
               TipVrijednosti operator [] (TipKljuca kljuc) const;
               void obrisi() { brisi(korijen); korijen=nullptr; broj=0; }
               void obrisi(const TipKljuca &kljuc);
        };
        
        template <typename TipKljuca, typename TipVrijednosti>
        void AVLStabloMapa<TipKljuca,TipVrijednosti>::brisi(AVLCvor<TipKljuca,TipVrijednosti>* covr)  {
            if(covr!=nullptr)  {
                brisi(covr->lijevi);
                brisi(covr->desni);
                delete covr;
            }
        }
        
        template <typename TipKljuca, typename TipVrijednosti>
        void AVLStabloMapa<TipKljuca,TipVrijednosti>::obrisi(const TipKljuca &kljuc) {
            AVLCvor<TipKljuca,TipVrijednosti>* p=korijen, *roditelj=nullptr;
            while (p!=nullptr && kljuc!=p->kljuc) {
                roditelj=p;
                if (kljuc<p->kljuc) p=p->lijevi;
                else p=p->desni;
          }
          if (p==nullptr) return;
          AVLCvor<TipKljuca,TipVrijednosti>* m;
          if (p->lijevi==nullptr) m=p->desni;
          else {
              if (p->desni==nullptr) m=p->lijevi;
              else {
                  AVLCvor<TipKljuca,TipVrijednosti>* pm=p, *tmp;
                  m=p->lijevi;
                  tmp=m->desni;
                  while (tmp!=nullptr) {
                      pm=m;
                      m=tmp;
                      tmp=m->desni;
                 }
                 if(pm!=p) {
                     pm->desni=m->lijevi;
                     m->lijevi=p->lijevi;
                }
                m->desni=p->desni;
            }
         }
         if (roditelj==nullptr) korijen=m;
         else {
             if(p==roditelj->lijevi) roditelj->lijevi=m,roditelj->balans--;
             else roditelj->desni=m,roditelj->balans++;
        }
        delete p;
        p=nullptr;
        broj--;
    }
    
    
    template<typename TipKljuca, typename TipVrijednosti>
    void AVLStabloMapa <TipKljuca, TipVrijednosti>:: ubaci(AVLCvor<TipKljuca, TipVrijednosti>* cvor){
        AVLCvor<TipKljuca, TipVrijednosti>* p= cvor->roditelj; 
        TipKljuca kljuc= cvor->kljuc; 
        if(p==nullptr) {
            korijen=cvor; 
            broj++; 
            return; 
        }
        if(p!=nullptr && (p->lijevi!=nullptr && p->desni!=nullptr)){
            if(kljuc<p->kljuc) p=p->lijevi; 
            else p=p->desni; 
            if(kljuc<p->kljuc) p->lijevi=cvor; 
            else p->desni=cvor; 
            azurirajBalans(cvor); 
            broj++; 
            return; 
        }
        else if(p!=nullptr){
            p->balans=0; 
            if(kljuc<p->kljuc) p->lijevi=cvor; 
            else p->desni=cvor; 
            broj++; 
            return; 
        }
    }
          
  template<typename TipKljuca, typename TipVrijednosti>
  void AVLStabloMapa<TipKljuca, TipVrijednosti>:: lijevaRotacija(AVLCvor<TipKljuca, TipVrijednosti>*cvor)
 {
     if(cvor->balans* cvor->desni->balans <0)
         desnaRotacija(cvor->desni); 
    AVLCvor<TipKljuca, TipVrijednosti>* temp= cvor->desni; 
    temp->roditelj= cvor->roditelj; 
    cvor->desni= nullptr; 
    temp->lijevi= cvor; 
    cvor->roditelj= temp; 
    temp->balans=0; 
    cvor->balans=0; 
    
 }
 
 template<typename TipKljuca, typename TipVrijednosti>
 void AVLStabloMapa<TipKljuca, TipVrijednosti>::desnaRotacija(AVLCvor<TipKljuca, TipVrijednosti>*cvor){
     if( cvor->balans*cvor->lijevi->balans<0)
        lijevaRotacija(cvor->lijevi); 
        AVLCvor<TipKljuca, TipVrijednosti>* temp= cvor->lijevi; 
        temp->roditelj= cvor->roditelj; 
        cvor->lijevi=nullptr; 
        temp->desni= cvor; 
        cvor->roditelj= temp; 
        temp->balans=0; 
        cvor->balans=0; 
 }

template<typename TipKljuca, typename TipVrijednosti>
void AVLStabloMapa<TipKljuca, TipVrijednosti>:: azurirajBalans(AVLCvor<TipKljuca, TipVrijednosti>* cvor){
   if(cvor== korijen) return; 
   AVLCvor<TipKljuca, TipVrijednosti> *p= cvor->roditelj; 
   if(p->lijevi== cvor) p->balans++; 
   else p->balans--; 
   if(p->balans>1) desnaRotacija(p); 
   else if(p->balans<-1) lijevaRotacija(p); 
   azurirajBalans(p); 
}

template<typename TipKljuca, typename TipVrijednosti>
AVLStabloMapa<TipKljuca, TipVrijednosti> & AVLStabloMapa<TipKljuca, TipVrijednosti>:: operator =(AVLStabloMapa && avl){
    if(this== & avl) return * this; 
    this->obrisi(); 
    korijen= avl.korijen; 
    broj=avl.broj; 
    return * this; 
}

template<typename TipKljuca, typename TipVrijednosti>
AVLStabloMapa<TipKljuca, TipVrijednosti> &AVLStabloMapa<TipKljuca, TipVrijednosti> :: operator =(const AVLStabloMapa & avl){
    if(this== & avl) return *this; 
    this->obrisi(); 
    preorderKopiraj(avl.korijen, korijen); 
    broj=avl.broj; 
    return *this; 
}

template<typename TipKljuca, typename TipVrijednosti>
void AVLStabloMapa<TipKljuca, TipVrijednosti>:: preorderKopiraj(AVLCvor<TipKljuca, TipVrijednosti>* cvor1, AVLCvor<TipKljuca, TipVrijednosti>* &cvor2, AVLCvor<TipKljuca, TipVrijednosti>* prethodni){
    if(cvor1!=nullptr){
        cvor2= new AVLCvor<TipKljuca, TipVrijednosti>(); 
        cvor2->kljuc= cvor1->kljuc; 
        cvor2->vrijednost= cvor1->vrijednost; 
        cvor2->roditelj= prethodni; 
        preorderKopiraj(cvor1->lijevi, cvor2->lijevi, cvor2); 
        preorderKopiraj(cvor1->desni, cvor2->desni, cvor2); 
        
    }
}

template<typename TipKljuca, typename TipVrijednosti>
AVLStabloMapa<TipKljuca, TipVrijednosti>:: AVLStabloMapa(const AVLStabloMapa & bsm): broj(bsm.broj){
    preorderKopiraj(bsm.korijen, korijen); 
}
 

template<typename TipKljuca, typename TipVrijednosti>
TipVrijednosti AVLStabloMapa<TipKljuca, TipVrijednosti>::operator [] (TipKljuca kljuc) const{
    AVLCvor<TipKljuca, TipVrijednosti> * temp= korijen; 
    while (temp!=nullptr && temp->kljuc != kljuc) {
        if(kljuc<temp->kljuc) temp=temp->lijevi; 
        else temp=temp->desni; 
    }

    if(temp==nullptr ) return TipVrijednosti(); 
    return temp->vrijednost; 
}

template<typename TipKljuca, typename TipVrijednosti>
TipVrijednosti & AVLStabloMapa<TipKljuca, TipVrijednosti>:: operator [](TipKljuca kljuc){
    AVLCvor<TipKljuca, TipVrijednosti>* p= korijen, *temp=korijen; 
    while (temp!=nullptr && temp->kljuc != kljuc) {
        p= temp; 
        if(kljuc<temp->kljuc) temp=temp->lijevi; 
        else temp=temp->desni; 
        
    }

   if(temp==nullptr){
        AVLCvor<TipKljuca, TipVrijednosti>* cvor= new AVLCvor<TipKljuca, TipVrijednosti>(); 
        cvor->kljuc=kljuc; 
        cvor->vrijednost= TipVrijednosti(); 
        cvor->lijevi=nullptr; 
        cvor->desni=nullptr; 
         cvor->roditelj=p; 
        cvor->balans=0; 
        ubaci(cvor); 
        return cvor->vrijednost; 
        
   }
    return temp->vrijednost; 
}

int main() {
 
    
    
    AVLStabloMapa<int, int> avl; 
    BinStabloMapa<int, int>bsm; 
    clock_t t1=clock(); 
    for(int i=0; i<7500; i++) bsm[i]= i; 
    clock_t t2= clock(); 
    clock_t t3= clock(); 
    for(int i=0; i<7500; i++) avl[i]= i; 
    clock_t t4= clock();  
    cout<<"Vrijeme unosa 7500 elemenata za binarno stablo je "<< (t2-t1)/(CLOCKS_PER_SEC/1000)<<"a za AVL stablo "<< (t4-t3)/(CLOCKS_PER_SEC/1000); 
    
    
    t1= clock(); 
    for(int i=0; i<7500; i++) bsm.obrisi(i); 
    t2=clock(); 
    t3=clock(); 
    for(int i=0; i<7500; i++) avl.obrisi(i); 
    t4=clock(); 
    cout<<(t2-t1)/(CLOCKS_PER_SEC/1000)<<(t4-t3)/(CLOCKS_PER_SEC/1000); 
    
    
    return 0;
}
