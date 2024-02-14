import { Injectable } from "@nestjs/common";
import { InjectRepository } from '@nestjs/typeorm';
import { Repository } from 'typeorm';
import { User } from '../entities/user.entity';
import { UserDto } from '../DTO/user.dto';
import { UserLoginDto } from "src/DTO/userLogin.dto";

@Injectable()
export class UsersService {
    constructor(
    @InjectRepository(User)
    private readonly userRepository: Repository<User>,
    ){}


    async createUser(UserDto: UserDto): Promise<User>  {
       
        const res =  await this.userRepository.findOne({where:{userName:UserDto.userName}});
        
        if (res !== null) {
            return null;
        }
        this.userRepository.create(UserDto);
        return this.userRepository.save(UserDto);
            
    }
    async getUserByUserName(username: string): Promise<User> {
        console.log('in get user function')
        return this.userRepository.findOne({where:{userName:username}});
       
    }
    
    
    async login(user:UserLoginDto):Promise<User> {
        return this.userRepository.findOne({where:{userName:user.username,password:user.password}})

    }
    async updateUser(user:UserDto):Promise<User> {
        console.log('in update user function')
        this.userRepository.update({userName:user.userName},{password:user.password});
        console.log('after update password')
        this.userRepository.update({userName:user.userName},{email:user.email});
        return this.userRepository.findOne({where:{userName:user.userName}});
    }
}