import { Entity, PrimaryGeneratedColumn, Column } from 'typeorm';

@Entity()
export class User {

  @PrimaryGeneratedColumn({
    type: 'bigint',
    name: 'user_id',
  })
  user_id: number;

  @Column({
    name: 'user_name',
    nullable: false,
    default: '',
  })
  userName: string;

  @Column({
    name: 'password',
    nullable: false,
    default: '',
  })
  password: string;

    @Column({
        name: 'email_address',
        nullable: false,
        default: '',
    })
    email: string;
}