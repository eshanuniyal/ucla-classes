function [] = exercise2(f, u, a, b, nValues)
% function to create graphs for exercise 2 given interval [a,b] assuming
% Dirichlet boundary conditions
% command for exercise 2: 
% exercise2(@(x) 32*pi^2*sin(2*pi*(2*x - 1)) + 40, @(x) 2*sin(2*pi*(2*x - 1)) - 20.*x.*(x - 1), 0, 1, [4 16 32 64])

    % iterating over nValues ( = [5, 10, 25, 50] in exercise 3)
    for n = nValues
        
        % creating matrix A
        A = zeros(n);
        % conditioning first row
        A(1,1) = 2; A(1, 2) = -1;
        % iterating over rows
        for r = 2:n-1
            A(r, r-1) = -1;
            A(r, r) = 2;
            A(r, r + 1) = -1;
        end
        % conditioning last row
        A(n, n-1) = -1; A(n, n) = 2;
        
        % creating b matrix
        nodes = linspace(a, b, n + 2);
        h = 1/(n+1);
        B = (h^2).*arrayfun(f, nodes(1:n));
        
        % finding U vector
        U = A \ B';
        % setting up U vector including Dirichlet boundary conditions
        UVals = zeros(1, n + 2);
        UVals(2:n+1) = U';
        
        x0 = 10; y0 = 10;
        width = 700; height = 500;
        
        % graphing u and Uvals
        figure(n);
        fplot(u, [a b]);
        hold on
        plot(nodes, UVals);
        hold off
        title("True solution u(x) and approximation using " + n + " equally-spaced nodes in (" + a + ", " + b + ")");
        legend('True solution', 'Approximation', 'Location', 'northwest');
        set(gcf,'position',[x0,y0,width,height])

    end


end



