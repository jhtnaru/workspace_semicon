`timescale 1ns / 1ps

// Button Input, LED Output
module button_led (
    input clk, reset,
    input btnL, btnR,
    output reg [7:0] JA
    );

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            JA <= 8'b0000_0000;
        end
        else begin
            if (btnL) begin
                JA <= 8'b0000_0000;
            end
            else if (btnR) begin
                JA <= 8'b1111_1111;
            end
        end
    end
endmodule

// Button Debounce
module button_debounce (
    input clk, reset,
    input noise_btn,            // Raw Input Button
    output reg clean_btn        // Modify Button
    );

    reg [19:0] cnt = 1;
    reg btn_sync_0, btn_sync_1; // 2단계
    reg btn_state;

    always @(posedge clk) begin
        btn_sync_0 <= noise_btn;
        btn_sync_1 <= btn_sync_0;
    end

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            cnt <= 1;
            btn_state <= 0;
            clean_btn <= 0;
        end
        else begin
            if (btn_sync_1 == btn_state) begin
                cnt <= 0;           // Input == 이전 State, 안정된 상태 → Counter Reset
            end
            else begin
                cnt <= cnt + 1;     // Inpue != 이전 State, Count 증가
                if (cnt >= 1_000_000) begin  // 1ms 유지 확인
                    btn_state <= btn_sync_1;
                    clean_btn <= btn_sync_1;
                    cnt <= 0;
                end
            end
        end
    end
endmodule

// Button Input Debounce, LED Output
module btn_led_blink (
    input clk, reset,
    input btnL, btnR,
    output reg [7:0] JA
    );

    wire btnL_clean;
    wire btnR_clean;

    button_debounce U1 (.clk(clk), .reset(reset),
        .noise_btn(btnL),           // 원래 Button
        .clean_btn(btnL_clean)      // Debounce된 출력
        );
    
    button_debounce U2 (.clk(clk), .reset(reset),
        .noise_btn(btnR),           // 원래 Button
        .clean_btn(btnR_clean)      // Debounce된 출력
        );

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            JA <= 8'b0000_0000;
        end
        else begin
            if (btnL_clean) begin
                JA <= 8'b0000_0000;
            end
            else if (btnR_clean) begin
                JA <= 8'b1111_1111;
            end
        end
    end
endmodule

// 
module btn_led_shift (
    input clk, reset,
    input btnL, btnR,
    output reg [7:0] JA
    );
    
    wire btnL_clean, btnR_clean;

    button_debounce U1 (.clk(clk), .reset(reset),
        .noise_btn(btnL),
        .clean_btn(btnL_clean)
        );
    
    button_debounce U2 (.clk(clk), .reset(reset),
        .noise_btn(btnR),
        .clean_btn(btnR_clean)
        );

    reg btnL_prev, btnR_prev;
    wire btnL_pressed = (btnL_clean == 1 && btnL_prev == 0);
    wire btnR_pressed = (btnR_clean == 1 && btnR_prev == 0);

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            btnL_prev <= 0;
            btnR_prev <= 0;
        end else begin
            btnL_prev <= btnL_clean;
            btnR_prev <= btnR_clean;
        end
    end

    always @(posedge clk or posedge reset) begin
        if (reset) begin
            JA <= 8'b0000_0000;
        end
        else begin
            if (btnL_pressed) begin
                if (JA == 8'b0000_0000 || JA == 8'b1000_0000) begin
                    JA <= 8'b0000_0001;
                end
                else begin
                    JA <= JA << 1;
                end
            end
            else if (btnR_pressed) begin
                if (JA == 8'b0000_0000 || JA == 8'b0000_0001) begin
                    JA <= 8'b1000_0000;
                end
                else begin
                    JA <= JA >> 1;
                end
            end
        end
    end
endmodule