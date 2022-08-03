#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include"header.h"


void init_stackoperand(stackoperand *s1, int len){
    s1->a = (number*)malloc(sizeof(number)*len);
    s1->size1= len;
    s1->top1= -1;
}
void init_stackoperator(stackoperator *s2,int len){
    s2->b = (char*)malloc(sizeof(char)*len);
    s2->size2=len;
    s2->top2=-1;
}
int isFulloperand(stackoperand s1) {
    if(s1.top1 == s1.size1-1)
        return 1;
    else
        return 0;
}

int isFulloperator(stackoperator s2){
    if(s2.top2==s2.size2-1)
        return 1;
    else
        return 0;
}

int isEmptyoperand(stackoperand s1) {
    if(s1.top1 == -1)
        return 1;
    else
        return 0;
}

int isEmptyoperator(stackoperator s2){
    if(s2.top2==-1)
        return 1;
    else
        return 0;
}
void pushoperand(stackoperand *s1, number n1){
    if(isFulloperand(*s1))
        return ;
    else {
        s1->top1++;
        s1->a[s1->top1] = n1;
        return;
    }
}

void pushoperator(stackoperator *s2,char c){
     if(isFulloperator(*s2))
        return;
     else{
        s2->top2++;
        s2->b[s2->top2]=c;
        return;
     }
}


char popoperator(stackoperator *s2){
    char e = '#';
    if(!isEmptyoperator(*s2)){
        e = s2->b[s2->top2];
        s2->top2--;
    }
    return e;
}

number popoperand(stackoperand *s1){
    number e;
    if(!isEmptyoperand(*s1)){
        e=s1->a[s1->top1];
        s1->top1--;
    }
    return e;
}

char peekoperator(stackoperator s2){
        return s2.b[s2.top2];
}

number peekoperand(stackoperand s1){
        return s1.a[s1.top1];
 }










void init(number *n){
    *n=NULL;
    return;
}

void add_term(number *n,int m){
     node *p,*newnode;
     newnode=(node*)malloc(sizeof(node));
     if(newnode){
        newnode->data=m;
        newnode->next=NULL;
        newnode->before=NULL;
     }
     else return;
     if(*n==NULL){
        *n=newnode;
         return;
     }
     p=*n;
     while(p->next){
        p=p->next;
     }
     newnode->before=p;
     p->next=newnode;
     newnode->next=NULL;
     return;
}

void add_before(number *n,int m){
     node *p,*newnode;
     newnode=(node*)malloc(sizeof(node));
     if(newnode){
        newnode->data=m;
        newnode->next=NULL;
        newnode->before=NULL;
     }
     else return;
     p=*n;
     newnode->before=p;
     p->before=newnode;
     newnode->next=p;
     *n=newnode;
     return;
}

void display(number n){
    node *p;
    p=n;
    while(p->data==0){
        if(!p->next){
            printf("%d",p->data);
            return;
        }
        p=p->next;
    }
    while(p){
        printf("%d",p->data);
        p=p->next;
    }
    return;
}


number addition(number n1,number n2){
     node *p,*q,*p1,*q1;
     int carry=0,sum,s;
     number n3;
     init(&n3);
     p1=n1;
     q1=n2;
     int len1=0,len2=0;
     while(p1->next){
        len1++;
        p1=p1->next;
     }
     while(q1->next){
        len2++;
        q1=q1->next;
     }
     while(len1<len2){
        add_before(&n1,0);
        len1++;
     }
     while(len2<len1){
         if(len1==len2)
              break;
        add_before(&n2,0);
        len2++;
     }

     p=n1;
     q=n2;
     while(p->next)
        p=p->next;
     while(q->next)
        q=q->next;
     while(p && q){
            sum=p->data+q->data+carry;
            s=sum%10;
            if(s==sum)
                carry=0;
            else
                carry=1;

        add_term(&n3,s);
        p=p->before;
        q=q->before;
     }
     if(carry==1)
        add_term(&n3,carry);
     p=n3;
     init(&n3);
     while(p->next)
        p=p->next;
     while(p){
        add_term(&n3,p->data);
        p=p->before;
     }
     p=n3;
     init(&n3);
     while(p->data==0){
         if(!p->next){
            add_term(&n3,p->data);
            return(n3);
        }
         p=p->next;
     }
     while(p){
        add_term(&n3,p->data);
        p=p->next;
     }
     return(n3);
}


number subtraction(number n1,number n2){
     node *p,*q,*p1,*q1,*p2,*q2;
     int borrow=0,diff;
     number n3,n4,n5,n6;
     init(&n3);
     init(&n4);
     init(&n5);
     init(&n6);
     p2=n1;
     q2=n2;
     int len1=0,len2=0;
     while(p2->next){
        len1++;
        p2=p2->next;
     }
     while(q2->next){
        len2++;
        q2=q2->next;
     }
     while(len1<len2){
        add_before(&n1,0);
        len1++;
     }
     while(len2<len1){
        add_before(&n2,0);
        len2++;
     }
     p2=n1;
     q2=n2;
     while(p2){
            add_term(&n5,p2->data);
            p2=p2->next;
       }
    while(q2){
            add_term(&n6,q2->data);
            q2=q2->next;
    }
    p=n5;
    q=n6;
    p1=n5;
    q1=n6;
    while(p1){
            if(p1->data<q1->data){
                p=n6;
                q=n5;
                borrow=1;
                break;
            }
            if(p1->data>q1->data)
                break;
        p1=p1->next;
        q1=q1->next;
     }
     while(p->next)
            p=p->next;
     while(q->next)
        q=q->next;
     while(p->before){
            diff=p->data-q->data;
            if(diff<0){
                diff=10+p->data-q->data;
                p=p->before;
                p->data=p->data-1;
            }
            else
                p=p->before;
            q=q->before;
            add_term(&n3,diff);
     }
     diff=p->data-q->data;
     add_term(&n3,diff);
     p=n3;
     while(p->next)
        p=p->next;
     while(p && p->data==0)
           p=p->before;
     if(borrow==1){
        add_term(&n4,-p->data);
        p=p->before;
     }
     while(p){
        add_term(&n4,p->data);
        p=p->before;
     }
     if(!n4)
        add_term(&n4,0);
     p=n4;
     init(&n4);
     while(p->data==0){
         if(!p->next){
            add_term(&n4,p->data);
            return(n4);
        }
         p=p->next;
     }
     while(p){
        add_term(&n4,p->data);
        p=p->next;
     }
     return(n4);
}

number multiplication(number n1,number n2){

     node *p,*q,*p1,*q1,*p2,*q2;
     number n3,n4;
     int mul,s,count=1,borrow=0;
     init(&n3);
     init(&n4);
     p2=n1;
     q2=n2;
     int len1=0,len2=0;
     while(p2){
        len1++;
        p2=p2->next;
     }
     while(q2){
        len2++;
        q2=q2->next;
     }
     while(len1<len2){
        add_before(&n1,0);
        len1++;
     }
     while(len2<len1){
        add_before(&n2,0);
        len2++;
     }
     p=n1;
     q=n2;
     p1=n1;
     q1=n2;
     while(p1){
        if(p1->data<q1->data){
           p=n2;
           q=n1;
           borrow=1;
           break;
        }
        if(p1->data>q1->data)
                break;
        p1=p1->next;
        q1=q1->next;
     }

     while(p->next){
        p=p->next;
     }
     while(p){
            if(borrow==1)
                q=n1;
            else
                q=n2;
            init(&n3);
            while(q->next){
                    q=q->next;
            }
            for(int i=1;i<count;i++)
                add_term(&n3,0);
            s=0;
            len2=len1;
            while(len2){
                 s=p->data*q->data+s;
                 mul=s%10;
                 s=(s-mul)/10;
                 add_term(&n3,mul);
                 if(!q->before)
                    add_term(&n3,s);
                 q=q->before;
                 len2--;
            }
            count++;
            p=p->before;
            if(!n4)
                add_term(&n4,0);
            p1=n3;
            init(&n3);
            while(p1->next)
                p1=p1->next;
            while(p1){
                add_term(&n3,p1->data);
                p1=p1->before;
            }
            n4=addition(n3,n4);
     }
     p=n4;
     init(&n4);
     while(p->data==0){
         if(!p->next){
            add_term(&n4,p->data);
            return(n4);
        }
         p=p->next;
     }
     while(p){
        add_term(&n4,p->data);
        p=p->next;
     }
     return(n4);
}

number division(number n1,number n2){
       node *p,*q,*m;
       number n3,n4,n5,n6;
       int borrow=0,z=0;
       init(&n3);
       init(&n4);
       init(&n5);
       init(&n6);
       p=n1;
       q=n2;
       while(q->next){
            if(q->data!=0){
                z=1;
                break;
            }
           q=q->next;
       }
       if(z==0 && q->data==0){
            printf("Division by ");
            add_term(&n6,0);
            return(n6);
       }
       q=n2;
       int len1=0,len2=0;
       while(p){
            len1++;
            p=p->next;
       }
       while(q){
            len2++;
            q=q->next;
       }
       while(len1<len2){
            add_before(&n1,0);
            len1++;
       }
       while(len2<len1){
            add_before(&n2,0);
            len2++;
       }
       p=n1;
       q=n2;
       while(p){
            add_term(&n3,p->data);
            p=p->next;
       }
       while(q){
            add_term(&n4,q->data);
            q=q->next;
       }
       p=n3;
       q=n4;
       while(p){
            if(p->data<q->data){
                borrow=1;
                break;
            }
            if(p->data>q->data){
                borrow=0;
                break;
            }
            if(p->data==q->data){
                borrow=2;
            }
            p=p->next;
            q=q->next;
       }
       p=n3;
       q=n4;
       if(borrow==1){
            add_term(&n5,0);
            return(n5);
       }
       if(borrow==2){
           add_term(&n5,1);
           return(n5);
       }
       add_term(&n6,1);
       while(1){
            len1=len2=0;
            while(p){
                len1++;
                p=p->next;
            }
            while(q){
                len2++;
                q=q->next;
            }
            p=n3;
            q=n4;
            if(len1<len2){
                while(q->data==0 && len1<len2){
                    q=q->next;
                    len2--;
                }
                if(len1<len2)
                    return(n5);
            }
            while(p){
                if(p->data<q->data){
                    borrow=1;
                    break;
                }
                if(p->data>q->data){
                    borrow=0;
                    break;
                }
                if(p->data==q->data)
                    borrow=2;
                p=p->next;
                q=q->next;
            }
            if(borrow==1){
                return(n5);
            }
            if(borrow==2){
                n5=addition(n5,n6);
                m=n5;
                return(n5);
            }
            n3=subtraction(n3,n4);

            if(!n5)
                add_term(&n5,0);
            n5=addition(n5,n6);
            p=n3;
            q=n4;
       }
}
















number mod(number n1,number n2){
       node *p,*q;
       number n3,n4,n5,n6;
       int borrow=0,z=0;
       init(&n3);
       init(&n4);
       init(&n5);
       init(&n6);
       p=n1;
       q=n2;
       while(q->next){
            if(q->data!=0){
                z=1;
                break;
            }
           q=q->next;
       }
       if(z==0 && q->data==0){
            printf("Modulus by ");
            add_term(&n6,0);
            return(n6);
       }
       q=n2;
       int len1=0,len2=0;
       while(p){
            len1++;
            p=p->next;
       }
       while(q){
            len2++;
            q=q->next;
       }
       while(len1<len2){

            add_before(&n1,0);
            len1++;
       }
       while(len2<len1){
            add_before(&n2,0);
            len2++;
       }
       p=n1;
       q=n2;
       while(p){
            add_term(&n3,p->data);
            p=p->next;
       }
       while(q){
            add_term(&n4,q->data);
            q=q->next;
       }
       p=n3;
       q=n4;
       while(p){
            if(p->data<q->data){
                borrow=1;
                break;
            }
            if(p->data>q->data){
                borrow=0;
                break;
            }
            if(p->data==q->data){
                borrow=2;
            }
            p=p->next;
            q=q->next;
       }
       p=n3;
       q=n4;
       if(borrow==1){
            return(n3);
       }
       if(borrow==2){
            add_term(&n6,0);
           return(n6);
       }
       while(1){
            len1=len2=0;
            while(p){
                len1++;
                p=p->next;
            }
            while(q){
                len2++;
                q=q->next;
            }
            p=n3;
            q=n4;
            if(len1<len2){
                while(q->data==0 && len1<len2){
                    q=q->next;
                    len2--;
                }
                if(len1<len2)
                    return(n3);
            }
            while(p){
                if(p->data<q->data){
                    borrow=1;
                    break;
                }
                if(p->data>q->data){
                    borrow=0;
                    break;
                }
                if(p->data==q->data)
                    borrow=2;
                p=p->next;
                q=q->next;
            }
            if(borrow==1)
                return(n3);
            if(borrow==2){
                add_term(&n6,0);
                return(n6);
            }
            n3=subtraction(n3,n4);
            add_term(&n6,1);
            if(!n5)
                add_term(&n5,0);
            n5=addition(n5,n6);
            init(&n6);
            p=n3;
            q=n4;
       }
}

number power(number n1,number n2){
      node *p,*q,*k;
      number n3,n4,n5;
      int z=0,m=0,n=0;
      init(&n3);
      init(&n4);
      init(&n5);
      p=n1;
      q=n2;
      while(p){
        add_term(&n3,p->data);
        p=p->next;
      }
      while(q){
        add_term(&n4,q->data);
        q=q->next;
      }
      add_term(&n5,1);
      p=n3;
      q=n4;
      while(1){
            z=0;
            n3=multiplication(n3,n1);
            n4=subtraction(n4,n5);
            q=n4;
            while(q->next){
                if(q->data!=0){
                   z=1;
                   break;
                }
                q=q->next;
            }
            if(z==0 && q->data==1){
                return(n3);
            }
      }

}
