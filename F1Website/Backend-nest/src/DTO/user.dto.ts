
import { IsString, IsEmail, IsNotEmpty, MinLength } from 'class-validator';

export class UserDto {
  @IsNotEmpty()
  @IsString()
  userName: string;

  @IsNotEmpty()
  @IsString()
  @MinLength(6)
  password: string;
  
  @IsNotEmpty()
  @IsEmail()
  email: string;
}
