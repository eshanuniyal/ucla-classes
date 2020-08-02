function [pNhat, his] = problem2(p0, g, maxIter)
    % Aitkens/Steffensen's Accelerated Convergence
    %   performs aitken's and Steffensen's to find fixed point of function g
    %
    %   inputs:
    %       p0      - initial guess
    %       g   - function to find p_n given p_{n-1}
    %       maxIter - maximum number of iterations
    %   
    %   outputs:
    %       p       - approximate root 
    %       his     - store looping history

    pN      = p0;
    pNp1    = g(pN);
    pNp2    = g(pNp1);

    % stores iter, pN, pNhat, steff_pN each iter
    his  = zeros(maxIter + 2, 4); 

    fprintf('\n\n ---- aitkens ---- \n\n')
    fprintf('iter\t\tpN\t\tpNHat\t\tsteff_pN\n');

    % generating first 100 terms given by standard fixed point iteration and
    % Aitken's method
    iter = 0;
    while iter<=maxIter

        pNhat   = pN - ((pNp1 - pN)^2)/(pNp2 - 2*pNp1 + pN);
        his(iter + 1,:) = [iter pN pNhat 0];

        pN = pNp1; pNp1 = pNp2; pNp2 = g(pNp2);
        iter = iter+1;

    end

    % generating first 100 terms given by Steffensen's method
    pN = p0;    % represents p^(N)_0
    pNp1 = g(pN);   % represents p^(N)_1
    pNp2 = g(pNp1); % represents p^(N)_2 (actual sequence)
    his(1, 4) = pNp2;  % inserting 0th element in his
    
    iter = 1;
    while iter <= maxIter
        pN = pN - ((pNp1 - pN)^2)/(pNp2 - 2*pNp1 + pN);
        pNp1 = g(pN);
        pNp2 = g(pNp1);
        his(iter + 1, 4) = pNp2;
        
        % print results
        if iter <= 10
            fprintf('%d\t\t%1.4e\t%1.4e\t%1.4e\n',his(iter, 1), his(iter, 2),his(iter, 3),pNp2);
        end
        iter = iter + 1;
    end
    
    disp('\n');
    
    % generating absolute differences
    delta_pN = zeros(1, maxIter);
    delta_pNhat = zeros(1, maxIter);
    delta_steff_pN = zeros(1, maxIter);
    iter = 1;
    while iter <= maxIter
        delta_pN(iter) = abs(his(iter + 1, 2) - his(iter, 2));
        delta_pNhat(iter) = abs(his(iter + 1, 3) - his(iter, 3));
        delta_steff_pN(iter) = abs(his(iter + 1, 4) - his(iter, 4));
        if iter <= 100
            fprintf('%d\t\t%1.4e\t%1.4e\t%1.4e\n', iter, delta_pN(iter), delta_pNhat(iter), delta_steff_pN(iter));
        end
        iter = iter + 1;
    end
    
    x0 = 10;
    y0 = 10;
    height = 600;
    width = 800;
    
    xLabels = linspace(0,100,100);
    % graphing results
    figure(1);
    plot(xLabels, delta_pN);
    title('Absolute difference $|p_{n+1} - p_n|$ using standard fixed point iteration', 'interpreter', 'latex');
    set(gcf,'position',[x0, y0, width, height]);
    
    figure(2);
    plot(xLabels, delta_pNhat);
    title("Absolute difference $|\hat{p}_{n+1} - \hat{p}_n|$ using Aitken's $\Delta^2$ method", 'interpreter', 'latex');
    set(gcf,'position',[x0, y0, width, height]);
    
    figure(3);
    plot(xLabels, delta_steff_pN);
    title("Absolute difference $|p^{(n+1)}_2 - p^{(n)}_2|$ using Steffensen's method", 'interpreter', 'latex');
    set(gcf,'position',[x0, y0, width, height]);
    
    % graphing all plots together
    figure(4);
    plot(xLabels, delta_pN);
    hold on
    plot(xLabels, delta_pNhat);
    plot(xLabels, delta_steff_pN);
    hold off
    title("Absolute differences from each method", 'interpreter', 'latex');
    legend("Standard Fixed Point Iteration", "Aitken's $\Delta^2$ Method", "Steffensen's Method", 'interpreter', 'latex');
    set(gcf,'position',[x0, y0, width, height]);

end
