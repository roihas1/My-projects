import { Entity, PrimaryColumn, Column } from 'typeorm';

@Entity('drivers')
export class Driver {
    @PrimaryColumn({
        unique: true,
    })
    driverId: string;

    @Column()
    givenName: string;

    @Column()
    familyName: string;

    @Column()
    dateOfBirth: string;

    @Column()
    nationality: string;

    @Column()
    url: string;

    @Column({
        default: '',
    })
    about: string;

    
}
