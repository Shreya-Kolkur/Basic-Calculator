#include <stdio.h>
#include <stdlib.h>
#include<limits.h>
#include<conio.h>
#include"header.h"

int precedence(char c){
    if(c=='+')
        return 10;
    else if(c=='-')
        return 10;
    else if(c=='*')
        return 20;
    else if(c=='/')
        return 20;
    else if(c=='(')
        return 5;
    else if(c == '%')
        return 20;
    else if(c == '^')
        return 30;
    return 0;
}
int main(){
    while(1){
    char E[1000099];
    gets(E);
    if(E[0]=='q')
        exit(0);
    stackoperand s1;
    stackoperator s2;
    stackoperator s3;
    init_stackoperand(&s1,1000999);
    init_stackoperator(&s2,1000999);
    init_stackoperator(&s3,1000999);
    number n1;
    char c;
    char d;
    int i=0;
    char j=' ';
    char k=' ';
    int count=0;
    int neg=0;
    if(E[0]!='(' && E[0]!='-' && ('0'>E[0] || E[0]>'9')){
            printf("error");
    }

    else{
            while(E[i]!='\0'){
                    neg=0;
                    c=E[i];
                    if((c=='-' && k=='o' && (peekoperator(s2)=='+' || peekoperator(s2)=='*' || peekoperator(s2)=='/' || peekoperator(s2)=='%' || peekoperator(s2)=='^' || peekoperator(s2)=='(')) || (c=='-'&& i==0)){
                        neg=1;
                        i++;
                    }
                    c=E[i];
                    if(c=='(' || c==')' || c=='+' || c=='-' || c=='/' || c=='*' || c=='%' || c=='^' || c==' ' || c=='\n' || ('0'<=c && c<='9')){
                    init(&n1);
                    if('0'<=c && c<='9'){
                            if(j=='i'){
                               printf("error");
                               exit(0);
                            }
                            while('0'<=c && c<='9'){
                                if(neg==1 && c!='0'){
                                   c=c-'0';
                                   c=-c;
                                   neg=0;
                                }
                                else
                                    c=c-'0';
                                add_term(&n1,(int)(c));
                                i++;
                                c=E[i];
                            }
                            pushoperand(&s1,n1);
                            j='i';
                            k=' ';
                    }
                    else if(c==' ')
                            i++;
                    else if(c=='\n');
                    else if(c=='('){
                            pushoperator(&s2,c);
                            i++;
                            count++;
                    }
                    else if(c==')'){
                            count--;
                            if(count<0){
                                printf("error");
                                exit(0);
                            }
                            while(peekoperator(s2)!='('){
                                d=popoperator(&s2);
                                if(d=='*'){
                                   node *p,*q,*d;
                                   p=popoperand(&s1);
                                   q=popoperand(&s1);
                                   while(p->next && p->data==0)
                                             p=p->next;
                                   while(q->next && q->data==0)
                                             q=q->next;
                                   if(p->data<0 && q->data>=0){
                                        p->data=-p->data;
                                        d=multiplication(p,q);
                                        while(d->data==0){
                                           d=d->next;
                                        }
                                        d->data=-d->data;
                                   }
                                   else if(q->data<0 && p->data>=0){
                                        q->data=-q->data;
                                        d=multiplication(p,q);
                                        while(d->data==0){
                                           d=d->next;
                                        }
                                        d->data=-d->data;
                                   }
                                   else if(q->data<0 && p->data<0){
                                        q->data=-q->data;
                                        p->data=-p->data;
                                        d=multiplication(p,q);
                                   }
                                   else
                                        d=multiplication(p,q);
                                   pushoperand(&s1,d);
                                }
                                else if(d=='/'){
                                    node *p,*q,*d;
                                    p=popoperand(&s1);
                                    q=popoperand(&s1);
                                    while(p->next && p->data==0)
                                             p=p->next;
                                    while(q->next && q->data==0)
                                             q=q->next;
                                    if(p->data<0 && q->data>=0){
                                       p->data=-(p->data);
                                       d=division(q,p);
                                       d->data=-d->data;
                                    }
                                    else if(q->data<0 && p->data>=0){
                                       q->data=-q->data;
                                       d=division(q,p);
                                       d->data=-d->data;
                                    }
                                     else if(q->data<0 && p->data<0){
                                            q->data=-q->data;
                                            p->data=-p->data;
                                            d=division(q,p);
                                    }
                                    else
                                       d=division(q,p);
                                    pushoperand(&s1,d);
                                }
                                else if(d=='+'){
                                   node *p,*q,*d;
                                   p=popoperand(&s1);
                                   q=popoperand(&s1);
                                   while(p->next && p->data==0)
                                             p=p->next;
                                   while(q->next && q->data==0)
                                             q=q->next;
                                   if(q->data<0 && p->data>=0){
                                      q->data=-q->data;
                                      pushoperand(&s1,subtraction(p,q));
                                   }
                                   else if(p->data<0 && q->data>=0){
                                      p->data=-p->data;
                                      pushoperand(&s1,subtraction(q,p));
                                   }
                                   else if(p->data<0 && q->data<0){
                                        p->data=-p->data;
                                        q->data=-q->data;
                                        d=addition(p,q);
                                        d->data=-d->data;
                                        pushoperand(&s1,d);
                                      }
                                   else
                                      pushoperand(&s1,addition(p,q));
                                }
                                else if(d=='-'){
                                      node *p,*q,*m;
                                      p=popoperand(&s1);
                                      q=popoperand(&s1);
                                      while(p->next && p->data==0)
                                             p=p->next;
                                      while(q->next && q->data==0)
                                             q=q->next;
                                      if(q->data<0 && p->data>=0){
                                         q->data=-q->data;
                                         m=addition(p,q);
                                         m->data=-m->data;
                                         pushoperand(&s1,m);
                                      }
                                      else if(p->data<0 && q->data>=0){
                                         p->data=-p->data;
                                         pushoperand(&s1,addition(p,q));
                                      }
                                      else
                                         pushoperand(&s1,subtraction(q,p));
                                }
                                else if(d=='%'){
                                    node *p,*q,*m;
                                    p=popoperand(&s1);
                                    q=popoperand(&s1);
                                    while(p->next && p->data==0)
                                            p=p->next;
                                    while(q->next && q->data==0)
                                            q=q->next;
                                    if(p->data<0 && q->data>=0){
                                            p->data=-(p->data);
                                            m=mod(q,p);
                                            m->data=-m->data;
                                    }
                                    else if(q->data<0 && p->data>=0){
                                            q->data=-q->data;
                                            m=mod(q,p);
                                            m->data=-m->data;
                                    }
                                    else if(q->data<0 && p->data<0){
                                            q->data=-q->data;
                                            p->data=-p->data;
                                            m=mod(q,p);
                                    }
                                    else
                                            m=mod(q,p);
                                    pushoperand(&s1,m);
                                }
                                else if(d=='^'){
                                     node *p,*q,*m;
                                     p=popoperand(&s1);
                                     q=popoperand(&s1);
                                     while(p->next && p->data==0)
                                           p=p->next;
                                     while(q->next && q->data==0)
                                            q=q->next;
                                     if(p->data<0){
                                            number n2;
                                            init(&n2);
                                            add_term(&n2,0);
                                            pushoperand(&s1,n2);
                                     }
                                     else if(q->data<0){
                                            number n2;
                                            init(&n2);
                                            add_term(&n2,2);
                                            q->data=-q->data;
                                            if(mod(p,n2)->data==0)
                                                pushoperand(&s1,power(q,p));
                                            else{
                                                m=power(q,p);
                                                m->data=-m->data;
                                                pushoperand(&s1,m);
                                            }
                                     }
                                     else
                                            pushoperand(&s1,power(q,p));
                                }
                            }
                            i++;
                            popoperator(&s2);
                    }
                    else if(c=='+' || c=='-' || c=='/' || c=='*' || c=='%' || c=='^'){
                            if(k=='o'){
                                printf("error");
                                exit(0);
                            }
                            if(isEmptyoperator(s2))
                               pushoperator(&s2, c);
                            else {
                                while(!isEmptyoperator(s2) && precedence(peekoperator(s2)) >= precedence(c)){
                                    d=popoperator(&s2);
                                    if(d=='*'){
                                        node *p,*q,*d;
                                        p=popoperand(&s1);
                                        q=popoperand(&s1);
                                        while(p->next && p->data==0)
                                             p=p->next;
                                        while(q->next && q->data==0)
                                             q=q->next;
                                        if(p->data<0 && q->data>=0){
                                            p->data=-p->data;
                                            d=multiplication(p,q);
                                            while(d->data==0){
                                                d=d->next;
                                            }
                                            d->data=-d->data;
                                        }
                                        else if(q->data<0 && p->data>=0){
                                            q->data=-q->data;
                                            d=multiplication(p,q);
                                            while(d->data==0){
                                                  d=d->next;
                                            }
                                            d->data=-d->data;
                                        }
                                        else if(p->data<0 && q->data<0){
                                            p->data=-p->data;
                                            q->data=-q->data;
                                            d=multiplication(p,q);
                                        }
                                        else
                                            d=multiplication(p,q);
                                        pushoperand(&s1,d);
                                    }
                                    else if(d=='/'){
                                         node *p,*q,*d;
                                         p=popoperand(&s1);
                                         q=popoperand(&s1);
                                         while(p->next && p->data==0)
                                             p=p->next;
                                        while(q->next && q->data==0)
                                             q=q->next;
                                         if(p->data<0 && q->data>=0){
                                            p->data=-(p->data);
                                            d=division(q,p);
                                            d->data=-d->data;
                                         }
                                          else if(q->data<0 && p->data>=0){
                                            q->data=-q->data;
                                            d=division(q,p);
                                            d->data=-d->data;
                                          }
                                          else if(q->data<0 && p->data<0){
                                            q->data=-q->data;
                                            p->data=-p->data;
                                            d=division(q,p);
                                          }
                                          else
                                            d=division(q,p);
                                          pushoperand(&s1,d);
                                    }
                                   else if(d=='+'){
                                       node *p,*q,*d;
                                       p=popoperand(&s1);
                                       q=popoperand(&s1);
                                       while(p->next && p->data==0)
                                             p=p->next;
                                       while(q->next && q->data==0)
                                             q=q->next;
                                       if(q->data<0 && p->data>=0){
                                          q->data=-q->data;
                                          pushoperand(&s1,subtraction(p,q));
                                       }
                                       else if(p->data<0 && q->data>=0){
                                          p->data=-p->data;
                                          pushoperand(&s1,subtraction(q,p));
                                       }
                                       else if(p->data<0 && q->data<0){
                                        p->data=-p->data;
                                        q->data=-q->data;
                                        d=addition(p,q);
                                        d->data=-d->data;
                                        pushoperand(&s1,d);
                                      }
                                       else
                                          pushoperand(&s1,addition(p,q));
                                    }
                                    else if(d=='-'){
                                          node *p,*q,*m;
                                          p=popoperand(&s1);
                                          q=popoperand(&s1);
                                          while(p->next && p->data==0)
                                             p=p->next;
                                          while(q->next && q->data==0)
                                             q=q->next;
                                          if(q->data<0 && p->data>=0){
                                             q->data=-q->data;
                                             m=addition(p,q);
                                             m->data=-m->data;
                                             pushoperand(&s1,m);
                                          }
                                          else if(p->data<0 && q->data>=0){
                                             p->data=-p->data;
                                             m=addition(p,q);
                                             pushoperand(&s1,m);
                                          }
                                          else
                                             pushoperand(&s1,subtraction(q,p));
                                     }
                                     else if(d=='%'){
                                            node *p,*q,*m;
                                            p=popoperand(&s1);
                                            q=popoperand(&s1);
                                            while(p->next && p->data==0)
                                                 p=p->next;
                                            while(q->next && q->data==0)
                                                 q=q->next;
                                            if(p->data<0 && q->data>=0){
                                                 p->data=-(p->data);
                                                 m=mod(q,p);
                                                 m->data=-m->data;
                                            }
                                            else if(q->data<0 && p->data>=0){
                                                 q->data=-q->data;
                                                 m=mod(q,p);
                                                 m->data=-m->data;
                                            }
                                            else if(q->data<0 && p->data<0){
                                                 q->data=-q->data;
                                                 p->data=-p->data;
                                                 m=mod(q,p);
                                            }
                                            else
                                                 m=mod(q,p);
                                            pushoperand(&s1,m);
                                     }
                                     else if(d=='^'){
                                            node *p,*q,*m;
                                            p=popoperand(&s1);
                                            q=popoperand(&s1);
                                            while(p->next && p->data==0)
                                                 p=p->next;
                                            while(q->next && q->data==0)
                                                 q=q->next;
                                            if(p->data<0){
                                                 number n2;
                                                 init(&n2);
                                                 add_term(&n2,0);
                                                 pushoperand(&s1,n2);
                                            }
                                            else if(q->data<0){
                                                 number n2;
                                                 init(&n2);
                                                 add_term(&n2,2);
                                                 q->data=-q->data;
                                                 if(mod(p,n2)->data==0)
                                                    pushoperand(&s1,power(q,p));
                                                 else{
                                                    m=power(q,p);
                                                    m->data=-m->data;
                                                    pushoperand(&s1,m);
                                                }
                                            }
                                            else
                                                    pushoperand(&s1,power(q,p));
                                     }

                                }
                                pushoperator(&s2,c);

                            }
                            i++;
                            j=' ';
                            k='o';
                    }
            }
            else{
                printf("error");
                exit(0);
            }
            }
            if(k=='o'){
                printf("error");
                exit(0);
            }
            if(count!=0){
                printf("error");
                exit(0);
            }
            while(!isEmptyoperator(s2)){
                    d=popoperator(&s2);
                    if(d=='*'){
                        node *p,*q,*d;
                        p=popoperand(&s1);
                        q=popoperand(&s1);
                        while(p->next && p->data==0)
                            p=p->next;
                        while(q->next && q->data==0)
                            q=q->next;
                        if(p->data<0 && q->data>=0){
                            p->data=-(p->data);
                            d=multiplication(q,p);
                            while(d->data==0){
                                d=d->next;
                            }
                            d->data=-d->data;
                        }
                        else if(q->data<0 && p->data>=0){
                            q->data=-(q->data);
                            d=multiplication(p,q);
                            while(d->data==0){
                                d=d->next;
                            }
                            d->data=-(d->data);
                        }
                        else if(p->data<0 && q->data<0){
                            p->data=-p->data;
                            q->data=-q->data;
                            d=multiplication(p,q);
                        }
                        else
                            d=multiplication(p,q);
                        pushoperand(&s1,d);
                    }
                    else if(d=='/'){
                        node *p,*q,*m;
                        p=popoperand(&s1);
                        q=popoperand(&s1);
                        while(p->next && p->data==0)
                            p=p->next;
                        while(q->next && q->data==0)
                            q=q->next;
                        if(p->data<0 && q->data>=0){
                            p->data=-(p->data);
                            m=division(q,p);
                            m->data=-m->data;
                        }
                        else if(q->data<0 && p->data>=0){
                            q->data=-q->data;
                            m=division(q,p);
                            m->data=-m->data;
                        }
                         else if(q->data<0 && p->data<0){
                            q->data=-q->data;
                            p->data=-p->data;
                            m=division(q,p);
                         }
                        else
                            m=division(q,p);
                        pushoperand(&s1,m);
                    }
                    else if(d=='+'){
                       node *p,*q,*d;
                       p=popoperand(&s1);
                       q=popoperand(&s1);
                       while(p->next && p->data==0)
                            p=p->next;
                       while(q->next && q->data==0)
                            q=q->next;
                       if(q->data<0 && p->data>=0){
                                q->data=-q->data;
                                pushoperand(&s1,subtraction(p,q));
                       }
                       else if(p->data<0 && q->data>=0){
                                p->data=-p->data;
                                pushoperand(&s1,subtraction(q,p));
                       }
                       else if(p->data<0 && q->data<0){
                                p->data=-p->data;
                                q->data=-q->data;
                                d=addition(p,q);
                                d->data=-d->data;
                                pushoperand(&s1,d);
                       }
                       else
                                pushoperand(&s1,addition(p,q));
                    }
                    else if(d=='-'){
                       node *p,*q,*m;
                       p=popoperand(&s1);
                       q=popoperand(&s1);
                       while(p->next && p->data==0)
                            p=p->next;
                       while(q->next && q->data==0)
                            q=q->next;
                       if(q->data<0 && p->data>=0){
                            q->data=-q->data;
                            m=addition(p,q);

                            while(m->data==0)
                                m=m->next;
                            m->data=-m->data;
                            pushoperand(&s1,m);
                       }
                       else if(p->data<0 && q->data>=0){
                            p->data=-p->data;
                           pushoperand(&s1,addition(p,q));
                       }
                       else
                        pushoperand(&s1,subtraction(q,p));
                    }
                    else if(d=='%'){
                        node *p,*q,*m;
                        p=popoperand(&s1);
                        q=popoperand(&s1);
                        while(p->next && p->data==0)
                            p=p->next;
                        while(q->next && q->data==0)
                            q=q->next;
                        if(p->data<0 && q->data>=0){
                            p->data=-(p->data);
                            m=mod(q,p);
                            m->data=-m->data;
                        }
                        else if(q->data<0 && p->data>=0){
                            q->data=-q->data;
                            m=mod(q,p);
                            m->data=-m->data;
                        }
                         else if(q->data<0 && p->data<0){
                            q->data=-q->data;
                            p->data=-p->data;
                            m=mod(q,p);
                         }
                        else
                            m=mod(q,p);
                        pushoperand(&s1,m);
                    }
                    else if(d=='^'){
                        node *p,*q,*m;
                        p=popoperand(&s1);
                        q=popoperand(&s1);
                        while(p->next && p->data==0)
                                p=p->next;
                        while(q->next && q->data==0)
                                q=q->next;
                        if(p->data<0){
                                number n2;
                                init(&n2);
                                add_term(&n2,0);
                                pushoperand(&s1,n2);
                        }
                        else if(q->data<0){
                            number n2;
                            init(&n2);
                            add_term(&n2,2);
                            q->data=-q->data;
                            if(mod(p,n2)->data==0)
                                pushoperand(&s1,power(q,p));
                            else{
                                m=power(q,p);
                                m->data=-m->data;
                                pushoperand(&s1,m);
                            }
                        }
                        else
                                pushoperand(&s1,power(q,p));
                    }
            }
            display(popoperand(&s1));

    }
       printf("\n");
    }
    return 0;
}
