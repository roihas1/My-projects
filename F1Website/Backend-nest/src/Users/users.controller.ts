import { Controller, Post, Body, Get, Param, Put } from '@nestjs/common';
import { UsersService } from './users.service';
import { UserDto } from '../DTO/user.dto';
import { UserLoginDto } from '../DTO/userLogin.dto';

@Controller('users')
export class UsersController {
  constructor(private readonly userService: UsersService) {}

  @Post('/createUser')
   async createUser(@Body() user: UserDto) {
    if ((await this.userService.createUser(user)) == null) {
      return 'User Name already exists - please choose another one';
    }
    return `User ${user.userName} created successfully!`;
  }

  @Get('username/:username')
  async getUser(@Param('username') username: string) {
    return this.userService.getUserByUserName(username);
  }
  @Get('login')
  async login(@Body() user: UserLoginDto) {
    const res = await this.userService.login(user);
    if (res == null) {
      return 'Login failed - username or password are incorrect';
    }
    return 'Login seccessful';
  }

  @Put('/updateUser')
  async updateUser(@Body() user: UserDto) {
    await this.userService.updateUser(user);
    return `User ${user.userName} updated successfully!`;
  }
}
