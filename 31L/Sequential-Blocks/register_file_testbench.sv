module regfile_tb;
	parameter sel = 32;
	parameter sel_size = 8;
	parameter sel_v_sz = 3;
	
	logic [sel_size-1:0][sel-1:0] row;
	//logic [sel_v_sz-1:0] sel;
	
	logic [sel_v_sz-1:0] raddr_1; // 3 bit read address 1
	logic [sel_v_sz-1:0] raddr_2; // 3 bit read addre=ss 2
	logic [sel_v_sz-1:0] waddr;   // 3 bit write address
	
	
	logic [sel-1:0] data_out_1; // 32 bit data out 1
	logic [sel-1:0] data_out_2; // 32 bit data out 2
	logic [sel-1:0] data_in;    // 32 bit data in
	
	int int_r1; // Index read address 1
	int int_r2; // Index read address 2
	int int_w;  // Index write address
	
	bit clk;
	bit rst_s;
	bit we;
	
	initial begin
		$display("\nReset (will always initially fail)");
		clk = 0;
		rst_s = 1;
		we = 1;
		
		raddr_1 = 0; int_r1 = 0;
		raddr_2 = 0; int_r2 = 0;
		waddr = 0;
		
		data_in = 4;

		for (int i = 0; i < sel_size-1; i++)
			row[i] = 0;

		#11
		$display("\nWriting");
		
		rst_s = 0;
		we = 1;
		
		raddr_1 = 0; int_r1 = 0;
		raddr_2 = 1; int_r2 = 1;
		waddr = 1;   int_w  = 1;

		#40
		$display("\nReset");
		rst_s = 1;
		for (int i = 0; i < sel_size-1; i++)
			row[i] = 0;

		#60
		$display("\nWriting");
		rst_s = 0;
		we = 1;
		
		raddr_1 = 4; int_r1 = 4;
		raddr_2 = 1; int_r2 = 1;
		waddr = 5;   int_w  = 5;

		#40
		$display("\nReading");
		we = 0;
		
		raddr_1 = 5; int_r1 = 5;
		raddr_2 = 2; int_r2 = 2;
		waddr = 3;   int_w  = 3;

		#40
		raddr_1 = 3; int_r1 = 3;
		raddr_2 = 3; int_r2 = 3;
		waddr = 3;   int_w  = 3;
		#40
		$finish;
	end
	
	always #5 clk = ~clk;

	always @(negedge clk) begin
		
		data_in = $urandom % 16;
		$display("write data: %b\n", data_in); 
	end

   regfile L1( .clk(clk), .we(we), .rst_s(rst_s), 
   .raddr_1(raddr_1), .raddr_2(raddr_2), .waddr(waddr), .rdata_1(data_out_1),
   .rdata_2(data_out_2), .wdata(data_in)); 
	
	always @(posedge clk)
	  #5 begin
		if(rst_s == 1)
		begin
			if (data_out_1 == 0 && data_out_2 == 0) begin
				$display("%t: PASS, Input: %b, Output (EXP/ACT1/ACT2) (%b/%b/%b)", $time, data_in, 0, data_out_1, data_out_2);	
			end
			else begin
				$display("%t: FAIL, Input: %b, Output (EXP/ACT1/ACT2) (%b/%b/%b)", $time, data_in, 0, data_out_1, data_out_2);	
			end
	        end
		else if (we == 1)
		begin
			if (data_out_1 == row[int_r1] && data_out_2 == row[int_r2]) begin
				$display("%t: PASS, Input: %b, Output (EXP1/ACT1) (EXP2/ACT2) (%b/%b) (%b/%b)", $time, data_in, row[int_r1], data_out_1, row[int_r2], data_out_2);	
			end
			else begin
				$display("%t: FAIL, Input: %b, Output (EXP1/ACT1) (EXP2/ACT2) (%b/%b) (%b/%b)", $time, data_in, row[int_r1], data_out_1, row[int_r2], data_out_2);	
			end

			row[int_w] = data_in;  
		end
		else if (we == 0)
		begin
			if (data_out_1 == row[int_r1] && data_out_2 == row[int_r2]) begin
				$display("%t: PASS, Input: %b, Output (EXP1/ACT1) (EXP2/ACT2) (%b/%b) (%b/%b)", $time, data_in, row[int_r1], data_out_1, row[int_r2], data_out_2);	
			end
			else begin
				$display("%t: FAIL, Input: %b, Output (EXP1/ACT1) (EXP2/ACT2) (%b/%b) (%b/%b)", $time, data_in, row[int_r1], data_out_1, row[int_r2], data_out_2);
			end
		end	
	end
endmodule
