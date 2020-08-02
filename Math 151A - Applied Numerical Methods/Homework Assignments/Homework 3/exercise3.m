function [] = exercise3(func, nNodes, nPoints)
% function to create graphs of a linear spline for exercise 3 given number
% of nodes nNodes and number of points to graph nPoints
% command for exercise 2: exercise2(@(x) 1/(1+x^2), -5, 5, [5 10 25 50])
    
    a = 0;
    b = 1;
    
    % generating n + 1 equally-spaced nodes
    xi_s = linspace(a, b, nNodes + 1);  % index 1 corresponds to x_0 and so on
    % computing values of f at each point
    fi_s = arrayfun(func, xi_s);
    
    % generating nPoints equally-distant points
    points = linspace(a, b, nPoints);
    % finding value of f (or func) for each point
    f_points = arrayfun(func, points);
    p_points = zeros(1, nPoints);

    pointIndex = 1; % starting pointIndex
    
    % iterating nNodes times to generate splines
    for i = 2:nNodes+1
        % generating spline between x_i and x_{i-1}
        p = @(x) fi_s(i) + (fi_s(i) - fi_s(i-1))/(xi_s(i) - xi_s(i-1)) * (x - xi_s(i));
        
        % computing p for all points in current interval
        while pointIndex <= nPoints && points(pointIndex) <= xi_s(i)
            p_points(pointIndex) = p(points(pointIndex));
            pointIndex = pointIndex + 1;
        end
    end
    
    % plotting graphs
    disp(max(abs(f_points - p_points)));
    plot(points, [p_points' f_points']);
        
end

