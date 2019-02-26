################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
Source/c/C6713Helper_UdeS.obj: ../Source/c/C6713Helper_UdeS.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv7/tools/compiler/c6000_7.4.20/bin/cl6x" -mv6700 --abi=coffabi -g --include_path="C:/ti/ccsv7/tools/compiler/c6000_7.4.20/include" --include_path="C:/ti/ccsv7/ccs_base/C6xCSL/include" --include_path="C:/ti/dsk6713/include" --define=CHIP_6713 --diag_warning=225 --diag_wrap=off --display_error_number --mem_model:const=far --mem_model:data=far --preproc_with_compile --preproc_dependency="Source/c/C6713Helper_UdeS.d" --obj_directory="Source/c" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

Source/c/main.obj: ../Source/c/main.c $(GEN_OPTS) | $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: C6000 Compiler'
	"C:/ti/ccsv7/tools/compiler/c6000_7.4.20/bin/cl6x" -mv6700 --abi=coffabi -g --include_path="C:/ti/ccsv7/tools/compiler/c6000_7.4.20/include" --include_path="C:/ti/ccsv7/ccs_base/C6xCSL/include" --include_path="C:/ti/dsk6713/include" --define=CHIP_6713 --diag_warning=225 --diag_wrap=off --display_error_number --mem_model:const=far --mem_model:data=far --preproc_with_compile --preproc_dependency="Source/c/main.d" --obj_directory="Source/c" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


