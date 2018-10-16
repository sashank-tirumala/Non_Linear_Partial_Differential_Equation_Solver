#include <iostream>
#include <cmath>
using namespace std;

template<class T>
class AD
{
  public:
    T f,fd,fdd;
      AD ()
      {
          f=0;
          fd=0;
          fdd=0;
      }
      AD (T fx,T fdx, T fddx)
      {
          f=fx;
          fd=fdx;
          fdd=fddx;
      }
      AD ADconst ();
      AD ADvar ();
      AD operator +();
      AD operator -();
      AD operator +(AD);
      AD operator -(AD);
      AD operator +(T);
      AD operator -(T);
      AD operator *(double);
      AD operator *(AD);
      AD operator /(T);
      AD operator /(AD);
      AD operator ^(AD);
      AD operator ^(T);
      template<class U>
      friend AD<U> operator +(U,AD<U>);
      template<class U>
      friend AD<U> operator -(U,AD<U>);
      template<class U>
      friend AD<U> operator *(U,AD<U>);
      template<class U>
      friend AD<U> operator /(U,AD<U>);
      template<class U>
      friend AD<U> operator ^(U,AD<U>);
      template<class U>
      friend AD<U> sin(AD<U>);
      template<class U>
      friend AD<U> cos(AD<U>);
      template<class U>
      friend AD<U> tan(AD<U>);
      template<class U>
      friend AD<U> cosec(AD<U>);
      template<class U>
      friend AD<U> sec(AD<U>);
      template<class U>
      friend AD<U> cot(AD<U>);
      template<class U>
      friend AD<U> asin(AD<U>);
      template<class U>
      friend AD<U> acos(AD<U>);
      template<class U>
      friend AD<U> atan(AD<U>);
      template<class U>
      friend AD<U> sinh(AD<U>);
      template<class U>
      friend AD<U> cosh(AD<U>);
      template<class U>
      friend AD<U> tanh(AD<U>);
      template<class U>
      friend AD<U> asinh(AD<U>);
      template<class U>
      friend AD<U> acosh(AD<U>);
      template<class U>
      friend AD<U> log(AD<U>);
      template<class U>
      friend AD<U> exp(AD<U>);
      void disp();
      template<class U>
      friend ostream& operator << (ostream& , AD<U>&);
      T dash()
      {
          return fd;
      }
      bool operator==(AD<T> &a)
      {
        if(f == a.f)
        {
          if(fd == a.fd)
          {
            if(fdd == a.fdd)
            {
              return 1;
            }
            else
            {
              return 0;
            }
          }
          else
          {
            return 0;
          }
        }
        else
        {
          return 0;
        }
      }

};

template<class T>
AD<T> AD<T>::ADconst ()
{
    AD v;
    v.f=f;
    v.fd=0;
    v.fdd=0;
    return v;
}

template<class T>
AD<T> AD<T>::ADvar ()
{
    AD v;
    v.f=f;
    v.fd=1;
    v.fdd=0;
    return v;
}

// Unary + and -
// ---------------------- //
template<class T>
AD<T> AD<T>::operator +()
{
    AD v;
    v.f=f;
    v.fd=fd;
    v.fdd=fdd;
    return v;
}
template<class T>
AD<T> AD<T>::operator -()
{
    AD v;
    v.f=-f;
    v.fd=-fd;
    v.fdd=-fdd;
    return v;
}
// ---------------------- //

//Binary +, -, *,/,^
// ---------------------- //
template<class T>
AD<T> AD<T>::operator +(AD g)
{
    AD h;
    h.f=f+g.f;
    h.fd=fd+g.fd;
    h.fdd=fdd+g.fdd;
    return h;
}

template<class T>
AD<T> AD<T>::operator +(T g)
{
    AD h;
    h.f=f + g;
    h.fd=fd;
    h.fdd=fdd;
    return h;
}
template<class T>
AD<T> operator +(T g, AD<T> f)
{
    AD<T> h;
    h.f=f.f+g;
    h.fd=f.fd;
    h.fdd=f.fdd;
    return h;
}

template<class T>
AD<T> AD<T>::operator -(AD g)
{
    AD h;
    h.f=f-g.f;
    h.fd=fd - g.fd;
    h.fdd=fdd - g.fdd;
    return h;
}

template<class T>
AD<T> AD<T>::operator -(T g)
{
    AD h;
    h.f=f - g;
    h.fd=fd;
    h.fdd=fdd;
    return h;
}
template<class T>
AD<T> operator -(T g, AD<T> f)
{
    AD<T> h;
    h.f=g-f.f;
    h.fd=-f.fd;
    h.fdd=-f.fdd;
    return h;
}

template<class T>
AD<T> AD<T>::operator *(AD g)
{
    AD h;
    h.f=f*g.f;
    h.fd=fd*g.f+g.fd*f;
    h.fdd=fdd*g.f+fd*g.fd+g.fdd*f+fd*g.fd;
    return h;
}
template<class T>
AD<T> AD<T>::operator *(double g)
{
    AD h;
    h.f=f*g;
    h.fd=fd*g;
    h.fdd=fdd*g;
    return h;
}
template<class T>
AD<T> operator *(T g, AD<T> f)
{
    AD<T> h;
    h.f=f.f*g;
    h.fd=f.fd*g;
    h.fdd=f.fdd*g;
    return h;
}
template<class T>
AD<T> AD<T>::operator /(AD g)
{
    AD<T> h;
    T numd;
    T dend;
    T num;
    T den;
    h.f=f/g.f;
    h.fd=(g.f*fd-g.fd*f)/(f*f);
    num = g.f*fd-g.fd*f;
    numd = g.fd*fd+g.f*fdd - g.fdd*f - g.fd*fd;
    den = g.f*g.f;
    dend = 2*g.f*g.fd;
    h.fdd= (den*numd - num*dend)/den;
    return h;
}
template<class T>
AD<T> AD<T>::operator /(T g)
{
    AD h;
    h.f=f/g;
    h.fd=fd/g;
    h.fdd=fdd/g;
    return h;
}
template<class T>
AD<T> operator /(T g, AD<T> f)
{
    // AD<T> h;
    // T numd;
    // T dend;
    // T num;
    // T den;
    // h.f=g/f.f;
    // h.fd=-g*f.fd/(f.f*f.f);
    // num = -g*f.fd;
    // den = f.f*f.f;
    // numd = -g*f.fdd;
    // dend = 2*f.f*f.fd;
    // h.fdd= (den*numd - num*dend)/den;

    AD<T> h = g*(f^-1);

    return h;
}
template<class T>
AD<T> AD<T>::operator ^(T g)
{

    AD v;
    v.f=pow(f,g);
    v.fd=g*pow(f,g-1);
    v.fdd=g*(g-1)*pow(f,g-2);
    return v;
}

template<class T>
AD<T> operator ^(T f, AD<T> g)
{
    AD<T> h;
    h.f = pow(f,g.f);
    h.fd = pow(f,g.f)*log(f)*g.fd;
    h.fdd = pow(f,g.f)*log(f)*log(f)*g.fd*g.fd+pow(f,g.f)*g.fdd*log(f);
    return h;
}

// ---- exp() ---- //
template<class T>
AD<T> exp(AD<T> f)
{
  AD<T> h;
  h.f = exp(f.f);
  h.fd = exp(f.f)*f.fd;
  h.fdd = exp(f.f)*f.fd*f.fd+ exp(f.f)*f.fdd;
  return h;

}
// ---- log() ---- //
template<class T>
AD<T> log(AD<T> f)
{
  AD<T> h;
  h.f = log(f.f);
  h.fd = f.fd/f.f;
  h.fdd = (f.f*f.fdd - f.fd*f.fd)/(f.f*f.f);
  return h;

}
// ---- trig() ---- //
template<class T>
AD<T> sin(AD<T> g)
{
    AD<T> h;
    h.f=sin(g.f);
    h.fd=cos(g.f)*g.fd;
    h.fdd=-sin(g.f)*g.fd*g.fd+cos(g.f)*g.fdd;
    return h;
}

template<class T>
AD<T> cos(AD<T> g)
{
    AD<T> h;
    h.f=cos(g.f);
    h.fd=-sin(g.f)*g.fd;
    h.fdd=-cos(g.f)*g.fd*g.fd-sin(g.f)*g.fdd;
    return h;
}

template<class T>
AD<T> tan(AD<T> g)
{
    AD<T> h;
    h.f=tan(g.f);
    h.fd=sec(g.f)*sec(g.f)*g.fd;
    h.fdd=2*sec(g.f)*sec(g.f)*tan(g.f)*g.fd*g.fd + sec(g.f)*sec(g.f)*g.fdd;
    return h;
}

template<class T>
AD<T> cot(AD<T> g)
{
    AD<T> h = 1/tan(g);
    return h;
}

template<class T>
AD<T> cosec(AD<T> g)
{
    AD<T> h = 1/sin(g);
    return h;
}

template<class T>
AD<T> sec(AD<T> g)
{
    AD<T> h = 1/cos(g);
    return h;
}

template<class T>
AD<T> asin(AD<T> g)
{
    AD<T> h;
    h.f = (T)asin(g.f);
    AD<T> temp1(g.fd, g.fdd, 0);
    AD<T> temp2 = (T)1/(((T)1 - g*g)^(T)0.5);
    h.fd = temp2.f*g.fd;
    h.fdd = temp2.fd*g.fd+temp2.f*g.fdd;
    return h;
}

template<class T>
AD<T> acos(AD<T> g)
{
    AD<T> h;
    h.f = (T)acos(g.f);
    AD<T> temp2 = (T)1/(((T)1 + g*g)^(T)0.5);
    h.fd = temp2.f*g.fd;
    h.fdd = temp2.fd*g.fd+temp2.f*g.fdd;
    return h;
}

template<class T>
AD<T> atan(AD<T> g)
{
    AD<T> h;
    h.f = (T)atan(g.f);
    AD<T> temp2 = (T)1/((T)1 + g*g);
    h.fd = temp2.f*g.fd;
    h.fdd = temp2.fd*g.fd+temp2.f*g.fdd;
    return h;
}

template<class T>
AD<T> sinh(AD<T> g)
{
    AD<T> h = (exp(g)-exp(-g))/2;
    return h;
}

template<class T>
AD<T> cosh(AD<T> g)
{
    AD<T> h = (exp(g)+exp(-g))/2;
    return h;
}

template<class T>
AD<T> tanh(AD<T> g)
{
    AD<T> h = sinh(g)/cosh(g);
    return h;
}

template<class T>
AD<T> asinh(AD<T> g)
{
    AD<T> h;
    AD<T> temp = (T)1/(((T)1+g^2)^(T)0.5);
    h.f = asinh(g.f);
    h.fd = temp.f*g.fd;
    h.fdd = temp.fd*g.fd+temp.f*g.fdd;

    return h;
}

template<class T>
AD<T> acosh(AD<T> g)
{
  AD<T> h;
  AD<T> temp = (T)1/(((T)1-g^2)^(T)0.5);
  h.f = asinh(g.f);
  h.fd = temp.f*g.fd;
  h.fdd = temp.fd*g.fd+temp.f*g.fdd;
  return h;
}

template<class T>
void AD<T>::disp()
{
  cout<<"("<<f<<" "<<fd<<" "<<fdd<<")";
}
template<class T>
ostream& operator<<(ostream& output, AD<T>& b)
{
  output<<"("<<b.f<<","<<b.fd<<","<<b.fdd<<")";
  return output;
}


// int main()
// {
//   AD<int> a(1,3,4);
//   a.disp();
//   cout<<a;
// }
