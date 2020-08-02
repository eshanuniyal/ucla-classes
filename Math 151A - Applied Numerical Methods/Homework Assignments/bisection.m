% This code was written for UCLA Math 151A (Spring 2020).
% The TA, Andrew Krieger, wrote the current version.
% The professor, Dr. Samy Wu Fung, provided a similar early version.
% 
% Note: you are welcome to refer to and run the code below when working on
% your homework, but you are strongly encouraged to write the bisection
% algorithm from scratch yourself to ensure you understand it and to
% practice numeric coding in MATLAB (or whatever language you choose).

function [root, history] = bisection(f, a, b, iterations)
%BISECTION Find a root of the function `f` between points `a` and `b`.
%    This function assumes that `a < b`, that `sign(f(a)) ~= sign(f(b))`,
%    and that neither `sign(f(a))` nor `sign(f(b))` is zero. The algorithm
%    always runs exactly `iterations` iterations, so the absolute error
%    will be less than `(b - a) / pow2(iterations)`.
%
%    The history output is a MATLAB struct, with fields 'left', 'right',
%    'mid', and 'fMid'. You can access these fields like this:
%
%        [root, history] = bisection(@some_func, 0, 1, 30);
%        disp(history.mid);       % An array of size 1x30.
%        disp(history.fMid(30));  % The value of some_func near the root.
%
%    You should call this function using a function handle for the first
%    argument. See
%    <https://www.mathworks.com/help/matlab/function-handles.html> or these
%    examples:
%
%        [root, history] = bisection(@sin, -0.5, 1, 30);
%        [root, history] = bisection(@(x) x - 3, 2, 5, 10);

    % Validate inputs.
    if iterations < 1
        fprintf("Error: iterations must be >= 1.\n");
        return;
    end
    if a >= b
        % We could swap `a` and `b` here instead. But it's also reasonable
        % to expect the caller to provide `a` and `b` in the correct order,
        % and indictate an error if not.
        fprintf("Error: a is not less than b.\n");
        return;
    end
    % Optimization: store f(a) and f(b) in variables, instead of repeatedly
    % calling f(...). It's not a big deal here, but this kind of
    % optimization can help in more performance-critical situations.
    fA = f(a);
    fB = f(b);
    if fA == 0 || fB == 0
        % We could just return a or b as a root instead of returning an
        % error. But for our homework, we assume that the bisection should
        % actually *run*, not just trivially find a root.
        fprintf("Error: zero value: f(a) = %f, f(b) = %f\n", fA, fB);
        return;
    end
    if sign(fA) == sign(fB)
        % This error isn't something we can practically recover from. Our
        % best choice is to throw an error here, e.g. by returning
        % immediately without setting the output `root`, or by using the
        % more complicated exceptions framework:
        % <https://www.mathworks.com/help/matlab/matlab_prog/throw-an-exception.html>
        fprintf("Error: same signs: f(a) = %f, f(b) = %f\n", fA, fB);
        return;
    end
    
    % This is initializing history as a MATLAB struct. struct variables
    % are a collection of named fields. In this case, each of the four
    % fields stores a row vector of length `iterations`.
    %
    % Instead of pre-allocating the row vectors with `zeros(...)`, we could
    % have just stored values like `history.left(iter) = a` inside our
    % loop. As always, the row vectors would expand as needed. That's
    % slightly less efficient than allocating the vector first with the
    % correct size then storing values into existing slots, which is why
    % many MATLAB authors prefer to pre-allocate.
    history.left = zeros(1, iterations);
    history.right = zeros(1, iterations);
    history.mid = zeros(1, iterations);
    history.fMid = zeros(1, iterations);
    
    for iter = 1:iterations
        mid = (a + b) / 2;
        fMid = f(mid);
        % Update history for this step.
        history.left(iter) = a;
        history.right(iter) = b;
        history.mid(iter) = mid;
        history.fMid(iter) = fMid;
        % Update a/b.
        if sign(fMid) == sign(fA)
            a = mid;
            fA = fMid;
        else
            b = mid;
        end
    end
    
    % If we didn't check that `iterations >= 1`, then it's possible that
    % the `for` loop never ran, and `mid` was never initialized.
    %
    % By the way, why did we check for `iterations >= 1` instead of
    % `iterations > 0`?
    root = mid;
end