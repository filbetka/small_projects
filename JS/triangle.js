function Triangle()
{
    // declaration
    let side_a, side_b, side_c;
    let side_for_height, height;

    // methods
    function Initialize(a, b, c)
    {
        side_a = a;
        side_b = b;
        side_c = c;
    }

    /**
     * @return {number}
     */

    function Area()
    {
        let half_circuit = (side_a + side_b + side_c) / 2;
        return Math.sqrt(
            half_circuit *
            (half_circuit - side_a) *
            (half_circuit - side_b) *
            (half_circuit - side_c));
    }

    // function Initialize(side, h)
    // {
    //     side_for_height = side;
    //     height = h;
    // }

    return {
        Initialize: Initialize,
        Area: Area
    }
}

let triangle = Triangle();
triangle.Initialize(3,4,5);
console.log(triangle.Area());