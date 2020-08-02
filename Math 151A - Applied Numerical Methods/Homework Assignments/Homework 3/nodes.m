function [nodeArray] = nodes(a, b, n, nodeType)
% function returns n + 1 nodes in the interval [a, b] depending on the type
% of nodes requested ("equally spaced" or "chebyshev")

    nodeArray = zeros(1, n+1);
    % we require n + 1 equally spaced nodes
    if strcmp(nodeType, 'equally spaced')
        nodeDist = (b - a) / n;
        for i = 1:n+1
           nodeArray(i) = a + (i-1)*nodeDist;
        end
    % we require n + 1 Chebyshev nodes    
    elseif strcmp(nodeType, 'chebyshev')
        for i = 1:n+1
            nodeArray(i) = (b+a)/2 - ((b-a)/2) * cos((2*(i-1) + 1)*pi/(2*n+2));
        end
    end

end