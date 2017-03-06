"""empty message

Revision ID: ca14aff3582f
Revises: 
Create Date: 2017-02-27 15:44:31.623000

"""
from alembic import op
import sqlalchemy as sa


# revision identifiers, used by Alembic.
revision = 'ca14aff3582f'
down_revision = None
branch_labels = None
depends_on = None


def upgrade():
    # ### commands auto generated by Alembic - please adjust! ###
    op.create_table('clients',
    sa.Column('id', sa.Integer(), nullable=False),
    sa.Column('ip_address', sa.String(length=20), nullable=True),
    sa.Column('lobby_id', sa.Integer(), nullable=True),
    sa.Column('created_date', sa.DateTime(), nullable=True),
    sa.ForeignKeyConstraint(['lobby_id'], ['lobbies.id'], ),
    sa.PrimaryKeyConstraint('id'),
    sa.UniqueConstraint('ip_address')
    )
    op.create_table('lobbies',
    sa.Column('id', sa.Integer(), nullable=False),
    sa.Column('num_players', sa.Integer(), nullable=True),
    sa.Column('max_players', sa.Integer(), nullable=True),
    sa.Column('created_date', sa.DateTime(), nullable=True),
    sa.Column('host_id', sa.Integer(), nullable=True),
    sa.ForeignKeyConstraint(['host_id'], ['clients.id'], ),
    sa.PrimaryKeyConstraint('id')
    )
    # ### end Alembic commands ###


def downgrade():
    # ### commands auto generated by Alembic - please adjust! ###
    op.drop_table('lobbies')
    op.drop_table('clients')
    # ### end Alembic commands ###
