`timescale 1ns / 1ps

// 1Hz 단위 LED Toggle
module led_blink_1hz (
    input clk, reset,
    output reg [7:0] led
    );

    reg clk_1hz;
    reg [26:0] count = 1;
    reg i = 7;

    // 1㎐ Clock 생성
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            count <= 0;
            clk_1hz <= 0;
        end
        else begin
            if (count >= 50_000_000) begin
                count <= 1;
                clk_1hz <= ~clk_1hz;
            end
            else begin
                count <= count + 1;
            end
        end
    end

    always @(posedge clk_1hz or posedge reset) begin
        if (reset) begin
            led <= 8'b00000000;
        end
        else begin
            led <= ~led;
        end
    end
endmodule

// Switch Input 따라 LED Shift
module led_shift (
    input clk, reset,
    input sw_1, sw_2,
    output reg [7:0] JA
    );
    
    reg clk_s;              // 분주된 Clock Signal
    reg [26:0] count = 1;   // 분주용 Count
    reg dir = 0;            // 왕복 Shift 방향
    integer i = 0;          // LED 위치

    // 1주기 0.5초 = 2㎐ Clock 생성
    always @(posedge clk or posedge reset) begin
        if (reset) begin
            count <= 0;
            clk_s <= 0;
        end
        else begin
            if (count >= 25_000_000) begin
                count <= 1;
                clk_s <= ~clk_s;            // 분주된 시간마다 Clock Signal 반전
            end
            else begin
                count <= count + 1;
            end
        end
    end

    always @(posedge clk_s or posedge reset) begin
        if (reset) begin
            JA <= 8'b00000000;      // Reset 값
        end
        else begin
            case ({sw_1, sw_2})
                2'b00 : begin       // Left Shift
                    // if (JA == 8'b10000000 || JA == 8'b00000000) begin
                    //     JA <= 8'b00000001;
                    // end
                    // else begin
                    //     JA <= JA << 1;
                    // end
                    JA <= 8'b00000000;
                    JA[i] <= 1'b1;
                    if (i >= 7) begin
                        i <= 0;
                    end
                    else begin
                        i <= i + 1;
                    end
                end
                2'b01 : begin       // Right Shift
                    // if (JA == 8'b00000001 || JA == 8'b00000000) begin
                    //     JA <= 8'b10000000;
                    // end
                    // else begin
                    //     JA <= JA >> 1;
                    // end
                    JA <= 8'b00000000;
                    JA[i] <= 1'b1;
                    if (i <= 0) begin
                        i <= 7;
                    end
                    else begin
                        i <= i - 1;
                    end
                end
                2'b10 : begin       // 1개 왕복 Shift
                    JA <= 8'b00000000;
                    JA[i] <= 1'b1;
                    if (dir == 1'b0) begin
                        if (i >= 6) begin
                            dir <= 1'b1;
                            i <= i + 1;
                        end
                        else begin
                            i <= i + 1;
                        end
                    end
                    else if (dir == 1'b1) begin
                        if (i <= 1) begin
                            dir <= 1'b0;
                            i <= i - 1;
                        end
                        else begin
                            i <= i - 1;
                        end
                    end
                end
                2'b11 : begin       // 2개 교차 왕복 Shift
                    case (i)
                        0, 6 : JA <= 8'b10000001;
                        1, 5 : JA <= 8'b01000010;
                        2, 4 : JA <= 8'b00100100;
                        3 : JA <= 8'b00011000;
                        default : JA <= 8'b00000000;
                    endcase
                    if (i >= 6) begin
                        i <= 1;
                    end
                    else begin
                        i <= i + 1;
                    end
                end
                default : JA <= 8'b00000000;
            endcase
        end
    end
endmodule