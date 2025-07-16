`timescale 1ns / 1ps

module tb_full_adder_structual;
    reg a, b, cin;
    wire sum, carry;

    full_adder_structual uut (
        .a(a),
        .b(b),
        .cin(cin),
        .sum(sum),
        .carry(carry)
    );

    initial begin
        $display("Time\t A B Cin | Sum Carry");
        $display("-------------------");
        $monitor("%4d\t %b %b  %b  |  %b    %b", $time, a, b, cin, sum, carry);

        a = 0; b = 0; cin = 0; #10;
        a = 0; b = 0; cin = 1; #10;
        a = 0; b = 1; cin = 0; #10;
        a = 0; b = 1; cin = 1; #10;
        a = 1; b = 0; cin = 0; #10;
        a = 1; b = 0; cin = 1; #10;
        a = 1; b = 1; cin = 0; #10;
        a = 1; b = 1; cin = 1; #10;
        $finish;
    end
endmodule

module tb_full_adder;
    reg a, b, cin;
    wire sum, carry;

    // 0 = behavioral, 1 = structual, 2 = dataflow
    parameter USE_FULLADDER = 0;

    generate
        if (USE_FULLADDER == 0) begin : behav
            full_adder_behavioral uut (
                .a(a),
                .b(b),
                .cin(cin),
                .sum(sum),
                .carry(carry)
            );
        end
        else if (USE_FULLADDER == 1) begin : struc
            full_adder_structual uut (
                .a(a),
                .b(b),
                .cin(cin),
                .sum(sum),
                .carry(carry)
            );
        end
        else if (USE_FULLADDER == 2) begin : dataf
            full_adder_dataflow uut (
                .a(a),
                .b(b),
                .cin(cin),
                .sum(sum),
                .carry(carry)
            );
        end
    endgenerate

    initial begin
        a = 0; b = 0; cin = 0;

        repeat (7) begin
            #10;
            {a, b, cin} = {a, b, cin} + 1;
        end
        #10;
        $finish;
    end

    initial begin
        $display("Time\t A B Cin | Sum Carry");
        $display("-------------------");
        $monitor("%4d\t %b %b  %b  |  %b    %b", $time, a, b, cin, sum, carry);
    end
endmodule

module tb_full_adder_4bit_structural;
    reg [3:0] a, b;
    reg cin;
    wire [3:0] sum;
    wire carry;

    full_adder_4bit_structural uut (
        .a(a),
        .b(b),
        .cin(cin),
        .sum(sum),
        .carry(carry)
    );

    initial begin
        $display("Time\tcin\ta   \tb   \t| sum \tcarry");
        $monitor("%4d\t%b  \t%b\t%b\t| %b\t%b", $time, cin, a, b, sum, carry);

        // Test
        cin = 0; a = 4'b0000; b = 4'b0000; #10;
        cin = 0; a = 4'b0001; b = 4'b0001; #10;
        cin = 1; a = 4'b0010; b = 4'b0011; #10;
        cin = 1; a = 4'b0110; b = 4'b0011; #10;
        cin = 0; a = 4'b1111; b = 4'b0001; #10;
        cin = 1; a = 4'b1010; b = 4'b0101; #10;
        cin = 0; a = 4'b1111; b = 4'b1111; #10;
        cin = 1; a = 4'b1111; b = 4'b1111;
        #10 $finish;
    end
endmodule

module tb_full_adder_sub_4bit_structural;
    reg [3:0] a, b;
    reg s;
    wire [3:0] sum;
    wire carry;

    full_adder_sub_4bit_structural uut (
        .a(a),
        .b(b),
        .s(s),
        .sum(sum),
        .carry(carry)
    );

    integer i, j;

    initial begin
        $display("Time\ta    b    s | sum  carry");
        $monitor("%4d\t%b %b %b | %b %b", $time, a, b, s, sum, carry);

        for (i = 0; i < 16; i = i + 1) begin
            for (j = 0; j < 16; j = j + 1) begin
                a = i;
                b = j;
                s = 0; #10;     // Add
                s = 1; #10;     // Sub
            end
        end
        $finish;
    end
endmodule

module tb_full_adder_sub_4bit;
    reg [3:0] a, b;
    reg s;
    wire [3:0] sum;
    wire carry;

    // 0 = behavioral, 1 = structual, 2 = dataflow
    parameter USE_ADD_SUB = 0;

    generate
        if (USE_ADD_SUB == 0) begin : behav
            full_adder_sub_4bit_behavioral uut (
                .a(a),
                .b(b),
                .s(s),
                .sum(sum),
                .carry(carry)
            );
        end
        else if (USE_ADD_SUB == 1) begin : struc
            full_adder_sub_4bit_structural uut (
                .a(a),
                .b(b),
                .s(s),
                .sum(sum),
                .carry(carry)
            );
        end
        else begin : dataf
            full_adder_sub_4bit_dataflow uut (
                .a(a),
                .b(b),
                .s(s),
                .sum(sum),
                .carry(carry)
            );
        end
    endgenerate

    integer i, j;

    initial begin
        $display("Time\ta    b    s | sum  carry");
        $monitor("%4d\t%b %b %b | %b %b", $time, a, b, s, sum, carry);

        for (i = 0; i < 16; i = i + 1) begin
            for (j = 0; j < 16; j = j + 1) begin
                a = i;
                b = j;
                s = 0; #10;     // Add
                s = 1; #10;     // Sub
            end
        end
        $finish;
    end
endmodule