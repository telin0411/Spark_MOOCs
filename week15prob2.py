# cook your code here
# Enter your code here. Read input from STDIN. Print output to STDOUT
def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)

def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        return False
    else:
        return x % m

def aoverbmod(a,b,p):
    return ((a%p) * modinv(b,p)) % p

def ret1(x):
    ret = 1
    for i in xrange(x-1):
        ret *= 10
        ret += 1
    return ret

fact = [1 for i in xrange(305)]
mod = 1000000007

for i in xrange(1,305):
    fact[i] = (fact[i-1] * i) % mod
    
def solve(x,y,z):
    s = x + y + z - 1
    den = fact[x] * fact[y] * fact[z]
    s_1 = fact[s]
    ans =  aoverbmod(ret1(s+1) * (4*x+5*y+6*z) * fact[s],den,mod)
    return ans

xyz = raw_input().split()
x = int(xyz[0])
y = int(xyz[1])
z = int(xyz[2])
ans = 0
for i in xrange(x+1):
    for j in xrange(y+1):
        for k in xrange(z+1):
            ans += solve(i,j,k)
print ans % mod
print ret1(50) % mod