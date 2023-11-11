import numpy as np
from scipy.optimize import newton


def ode_solve(alpha, beta, a, b, N, f, g):
    h = (b - a) / N
    x = np.linspace(a, b, N + 1)

    # Define the system of ODEs
    def ode_system(y, x):
        y1, y2 = y
        return [y2, f(x) * y1 + g(x) * y2]

    # Define the boundary conditions
    def bc(ya, yb):
        return [ya[0] - alpha, yb[0] + beta * ya[1] - beta * g(b)]

    # Solve the system of ODEs using finite differences and shooting method
    y_guess = [alpha, 0.1]
    y1, y2 = shooting_method(ode_system, bc, y_guess, x)

    # Return the solution
    return x, y1


def shooting_method(ode_system, bc, y_guess, x):
    def residual(y_guess, alpha, beta):
        sol = odeint(ode_system, y_guess, x)
        return bc(sol[0], sol[-1], alpha, beta)

    # Use the Newton method to solve the residual equation
    y1_guess, y2_guess = y_guess
    y1_sol, y2_sol = newton(residual, [y1_guess, y2_guess], args=(alpha, beta))

    # Solve the ODE system with the optimized initial conditions
    sol = odeint(ode_system, [y1_sol, y2_sol], x)
    return sol[:, 0], sol[:, 1]


# Define the ODE parameters
alpha = 1
beta = -2
a = 0
b = 2
N = 100
f = lambda x: 1 / x
g = lambda x: -3

# Solve the ODE and plot the results
x, y = ode_solve(alpha, beta, a, b, N, f, g)
plt.plot(x, y)
plt.xlabel("x")
plt.ylabel("y")
