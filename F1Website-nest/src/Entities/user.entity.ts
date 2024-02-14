// src/entities/user.entity.ts
import { Entity, Column, PrimaryGeneratedColumn } from 'typeorm';

@Entity('user')
export class User {
  @PrimaryGeneratedColumn()
  user_id: number;

  @Column({ length: 100 ,
  default: 'Error',
  unique: true,})
  userName: string;

  @Column({ length: 100,default: 'Error' })
  email: string;

  @Column({ length: 100,default: 'Error' })
  password: string;
}
